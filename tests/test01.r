cat('###PyRInText2019###')
cat(21)
cat('###PyRInText2019###')

mcPi <- function(points){ # This is R comment
	inR <- 0
	cols <- NULL
	range <- c(0,1)
	x <- runif(points,0,1)
	y <- runif(points,0,1)
	r <- x^2+y^2
	for(i in r){
		if(i<=1){
			inR <- inR + 1
			cols <- c(cols,"red")
		}
		else
		  cols <- c(cols,"black")
	}
	return_data <- 4*inR/points

	pdf("mc_pi.pdf") 
	plot(x,y,col=cols,xlim=range,ylim=range,pch=20,
		main="Estimate pi value with Monte Carlo method",
		sub=sprintf("%s points. pi = %1.6f",points, return_data))
	curve(sqrt(1-x^2),xlim=c(0,1),ylim=c(0,1),add=T)
	lines(c(0,1),c(0,0))
	lines(c(0,0),c(1,0))
	return(return_data)
}

cat('###PyRInText2019###')
cat(91)
cat('###PyRInText2019###')
points<-2003
cat('###PyRInText2019###')
cat(93)
cat('###PyRInText2019###')
cat(points)
cat('###PyRInText2019###')
cat(95)
cat('###PyRInText2019###')
cat(mcPi(points))
cat('###PyRInText2019###')
cat(103)
cat('###PyRInText2019###')
library(knitr);data(iris);data<-iris[c(41:60),];kable(data, "latex")
