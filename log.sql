-- Keep a log of any SQL queries you execute as you solve the mystery.

.schema crime_scene_reports

SELECT description FROM crime_scene_reports WHERE year='2020' AND month='7' AND day='28';
-- Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse. Interviews were conducted today with three witnesses who were present at the time 
-- — each of their interview transcripts mentions the courthouse.

SELECT name, transcript FROM interviews WHERE year='2020' AND month='7' AND day='28';
-- RUTH\ Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. 
--If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.

--EUGENE\ I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.

--RAYMOND\ As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. 
--The thief then asked the person on the other end of the phone to purchase the flight ticket.

SELECT activity, license_plate, hour, minute FROM courthouse_security_logs WHERE year='2020' AND month='7' AND day='28' ORDER BY hour;

SELECT id, account_number, amount FROM atm_transactions WHERE year='2020' AND month='7' AND day='28' AND atm_location='Fifer Street' AND transaction_type='withdraw';
--id | account_number
--246 | 28500762
--264 | 28296815
--266 | 76054385
--267 | 49610011
--269 | 16153065
--288 | 25506511
--313 | 81061156
--336 | 26013199

SELECT name, phone_number, passport_number, license_plate FROM people WHERE license_plate='5P2BI95' OR license_plate='94KL13X' OR license_plate='6P58WS2' OR license_plate='4328GD8' OR license_plate='G412CB7' OR license_plate='L93JTIZ' OR license_plate='322W7JE' OR license_plate='0NTHK55'; 
-- obtain names of license plates that are suspected. 

SELECT name, account_number, passport_number, license_plate, phone_number FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE account_number = '28500762' OR account_number = '28296815' OR account_number = '76054385' OR account_number = '49610011' OR account_number = '16153065'OR account_number = '25506511' OR account_number = '81061156' OR account_number = '26013199';
-- obtain names of account numbers that are suspected.

SELECT full_name, city, hour, minute, destination_airport_id, flights.id FROM airports 
JOIN flights ON airports.id = flights.origin_airport_id
WHERE year='2020' AND month='7' AND day='29' ORDER BY hour;
-- obtain flight details (destination, time of flight)

SELECT * FROM airports
-- see list of airports details

SELECT passport_number, seat FROM passengers
JOIN flights ON passengers.flight_id = flights.id
WHERE flights.id = '36';

SELECT caller, receiver, duration FROM phone_calls WHERE year='2020' AND month='7' AND day='28' AND caller ='(367) 555-5533' OR caller = '(389) 555-5198' ORDER BY caller;
-- obtain list of phonecalls from Ernest and Danielle on day of thef 

SELECT name, phone_number FROM people WHERE phone_number = '(375) 555-8161';
-- obtain name of accomplice