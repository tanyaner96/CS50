--In 7.sql, write a SQL query to list all movies released in 2010 and their ratings, in descending order by rating. For movies with the same rating, order them alphabetically by title.
--Your query should output a table with two columns, one for the title of each movie and one for the rating of each movie.
--Movies that do not have ratings should not be included in the result.

--SELECT rating FROM ratings WHERE movie_id IN (SELECT id FROM movies WHERE year = '2010'); -- ratings of movies in 2010 

SELECT title, rating FROM movies

JOIN ratings ON movies.id = ratings.movie_id

ORDER BY rating desc, title asc;

