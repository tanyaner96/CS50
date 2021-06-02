import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/", methods=["GET", "POST"])
@login_required
def index():
    """Show portfolio of stocks"""
    user_cash = db.execute("SELECT cash from users WHERE id = ?", session["user_id"])[0]["cash"]
    stocks = db.execute("SELECT symbol, SUM(shares) as shares, operation, price FROM stocks WHERE userID = ? GROUP BY symbol HAVING (SUM(shares)) > 0;", session["user_id"])

    total_stocks = 0

    for stock in stocks:
        quote = lookup(stock["symbol"])
        stock["name"] = quote["name"]
        stock["total"] = round(float(quote["price"] * stock["shares"]),2)
        stock["price"] = quote["price"]
        total_stocks = total_stocks + stock["total"]
    total_cash = total_stocks + user_cash

    if request.method == "POST":
        add_amt = request.form.get("add")
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", add_amt, session["user_id"])
        return render_template("index.html", stocks = stocks, user_cash = user_cash, total_cash = total_cash)
    else:

        return render_template("index.html", stocks = stocks, user_cash = user_cash, total_cash = total_cash)




@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        price = lookup(symbol)
        user_cash = db.execute("SELECT cash from users WHERE id = ?", session["user_id"])[0]["cash"]

        #Check for blank submission
        if not symbol:
            return apology("Please input stock symbol", 400)
        #Check for valid symbol
        elif not lookup(symbol):
            return apology("Please input a valid stock symbol", 400)
        #Check if stock exists
        elif price is None:
            return apology("Sorry, stock does not exist", 400)

        #Check if shares is positive integer
        try:
            val = int(shares)
            if val < 0:
                return apology("Unable to buy less than 1 share", 400)
        except ValueError:
            return apology("Please input a whole number", 400)

        
        cost = (price["price"]) * float(shares)


        if user_cash < cost:
            return apology("Insufficient funds", 400)

        else:
            db.execute("INSERT INTO stocks (symbol, shares, price, operation, userID) VALUES (?, ?, ?, ?, ?)", symbol, shares, price["price"], "buy", session["user_id"])
            return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    stocks = db.execute("SELECT * FROM stocks WHERE userID = ?", session["user_id"])
    return render_template("history.html", stocks = stocks)



@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        quote1 = lookup(symbol)

        if quote1 is None:
            return apology("Please input valid symbol.", 400)

        else:
            return render_template("quoted.html", name=quote1["name"], symbol=quote1["symbol"], price=quote1["price"],)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        #Check for blank submissions.
        if not username:
            return apology("please provide a username.", 400)
        elif not password:
            return apology("please provide a password.", 400)
        elif confirmation != password:
            return apology("passwords do not match.", 400)

        #Check for existing users.
        else:
            check = db.execute("SELECT * FROM users WHERE username = ?", username)

            #If user doesn't exist, register user
            if len(check) == 0:
                hash = generate_password_hash(password, method='pbkdf2:sha256', salt_length=8)
                db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
                return redirect("/")
            else:
                return apology ("user already exists, please try another username.", 400)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        price = lookup(symbol)["price"]
        shares_value = price * shares

        if not symbol:
            return apology("Please input stock symbol", 400)
        elif price is None:
            return apology("Sorry, stock does not exist", 400)

        try:
            val = int(shares)
            if val < 0:
                return apology("Unable to buy less than 1 share", 400)
        except ValueError:
            return apology("Please input a whole number", 400)

        stocks = db.execute("SELECT SUM(shares) as shares FROM stocks WHERE userID = ? AND symbol = ?;", session["user_id"], symbol)[0]

        if shares > stocks["shares"]:
            return apology("You have exceeded the number of shares available.", 400)

        db.execute("INSERT INTO stocks (userID, symbol, shares, price, operation) VALUES (?, ?, ?, ?, ?)", session["user_id"], symbol, -shares, price, "sell")

        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", shares_value, session["user_id"])

        return redirect("/")

    else:
        stocks = db.execute("SELECT symbol FROM stocks WHERE userID = ? GROUP BY symbol", session["user_id"])
        return render_template("sell.html", stocks = stocks)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
