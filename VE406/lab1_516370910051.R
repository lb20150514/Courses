# Task 1 part(a) --------------------------------------------
# >? round
# >?? regression

# '? function':
#   return help of the function and description of its related functions
# '?? concept':
#   return a list of URL links to functions based on the concept


# Task 1 part(b) --------------------------------------------
x <- 1/7
print(x,15)


# Task 1 part(c) --------------------------------------------
# >demo(graphics)

# We use 'coplot()' when drawing conditioning plots.


# Task 1 part(d) --------------------------------------------
# >.1 == 0.1
# [1] TRUE
# >.1 + .2 == .3
# [1] FALSE

# Numbers are stored in binary form in computer. 
# For example, 0.1 is stored as 
#   0.000110011...(64 bits in total)
#   so 0.1 is not exactly 0.1.
# When judging (.1 == 0.1), that is okay.
# When judging (.1 + .2 == .3), the slight difference 
#   will cause inequality.


# Task 1 part(e) --------------------------------------------
y.vec <- rep(-1,200)
for (i in 1:100){
  y.vec[2 * i - 1] <- i
}


# Task 2 part(a) --------------------------------------------
# i)    z[1]
# ii)   z[2:5]
# iii)  z[1:(length(z)-2)]
# iv)   z[c(seq(1,length(z),by=2))]
# v)    z[z>0]
# vi)   z[!is.na(z)]
# vii)  z[c(seq(2,length(z),by=3))]


# Task 2 part(b) --------------------------------------------
# The first line links data in z to name of states.
# The second line extracts data in z corresponding to michigan.


# Task 2 part(c) --------------------------------------------
# i)    m.mat[1:2,]
# ii)   m.mat[row(m.mat)==2 & m.mat>log2(10)]


# Task 2 part(d) --------------------------------------------
# The first nine elements in m.mat, count from up to down 
#   in column, then from left to right in row.


# Task 2 part(e) --------------------------------------------
# i)    m.df[1:2,]
# ii)   m.df[row(m.df)==2 & m.df>log2(10)]


# Task 2 part(f) --------------------------------------------
# m.mat is a "matrix" that restores data in "numeric" type, 
# while m.df is a "data.frame" restores data in "integer" type 
#   in three objects.
# The data are equal in value and can be called by index 
#   col/row nams.


# Task 3 part(a) --------------------------------------------
grade = data.frame(
  gindex = (1:5),
  grade = c("A", "B", "C", "D", "F"),
  desc = c("Excellent", "Good", "Satisfactory", "Poor", 
           "Inadequate")
)
student = data.frame(
  gindex = c(3,3,4,1,1,2,2,2,2,1,2,3,1,2,5,1,2,1,4,1,1,1,3,3,1,
             3,2,2,1,2,3,2,1,1,2,3,3,2,3,2),
  fail = c(rep(FALSE,14), TRUE, rep(FALSE,25)),
  gender = c(rep("Female",20), rep("Male",20)),
  proj = c(rep(18,6),rep(17,4), rep(16,3), rep(15,7), rep(18,5),
           rep(17,4), rep(16,5), rep(15,6))
)
gradebook.df = merge(grade, student, by.x = "gindex",by.y = "gindex")


# Task 3 part(b) --------------------------------------------



# Task 3 part(c) --------------------------------------------
mean_project <- aggregate(gradebook.df["proj"],by=gradebook.df["grade"],FUN=mean)


# Task 3 part(d) --------------------------------------------
index <- as.character(sample(1:40,10))
rand_sample <- gradebook.df[index,]


# Task 4 part(a) --------------------------------------------
noral_sample <- rnorm(100,4,2)
hist(noral_sample)


# Task 4 part(b) --------------------------------------------
hist(noral_sample,freq = F)
par(new = T)
curve(dnorm(x, 4, 2), from = 0, to = 10, yaxt = "n", ylab = "")


# Task 4 part(c) --------------------------------------------



# Task 5 part(a) --------------------------------------------
chisqdens.plot <- function(nu){
  x <- seq(from = 0, to = qchisq(0.999,nu), by = 0.001)
  y <- rchisq(x,nu)
  plot(density(y), xlim = c(0,qchisq(0.999,nu)))
}
chisqdens.plot(2)


# Task 5 part(b) --------------------------------------------
chisqdens.plot <- function(nu.vec){
  xmax <- max(qchisq(0.999,nu.vec))
  x <- seq(from = 0, to = xmax, by = 0.001)
  y <- rchisq(x,nu.vec[1])
  plot(density(y), xlim = c(0,xmax))
  for (i in 2:length(nu.vec)) {
   lines(density(rchisq(x,nu.vec[i]))) 
  }
}
chisqdens.plot(c(2,4,8,16))


# Task 5 part(c) --------------------------------------------
chisqdens.plot <- function(nu.vec){
  a = 0.25
  xmax <- max(qchisq(0.999,nu.vec))
  x <- seq(from = 0, to = xmax, by = 0.001)
  y <- rchisq(x,nu.vec[1])
  plot(density(y), xlim = c(0,xmax), type = "h", 
       col = hsv(1,1,1,a))
  for (i in 2:length(nu.vec)) {
    lines(density(rchisq(x,nu.vec[i])),type = "h", 
          col = hsv(1/i,1,1/i,a)) 
  }
}
chisqdens.plot(c(2,4,8,16))


# Task 6 part(a) --------------------------------------------
# data (" faithful ") # load built in data set
# ? faithful
# eruptions	is "numeric" type data records eruption time in mins
# waiting	is "numeric" type date records Waiting time to 
#   next eruption (in mins)


# Task 6 part(b) --------------------------------------------
hist(faithful[,2])
hist(faithful[,2],breaks = 20)
plot(density(faithful[,2]))


# Task 6 part(c) --------------------------------------------
qqnorm(faithful[,2])
# The QQ plot shows that "waiting" cannot follows a 
#   normal distribution

# Task 6 part(d) --------------------------------------------
plot(faithful[,2], faithful[,1], xlab = "waiting", 
     ylab = "eruption")
lines(lowess(faithful[,2],faithful[,1]), col = 2)
# The plot means that waiting time and eruption time are 
#   positive correlated.

# Task 7 ----------------------------------------------------
library(lattice)
# Cite from help of xyplot
EE <- equal.count(ethanol$E, number=9, overlap=1/4)

xyplot(NOx ~ C | EE, data = ethanol,
       prepanel = function(x, y) prepanel.loess(x, y, span = 1),
       xlab = "Compression Ratio", ylab = "NOx (micrograms/J)",
       panel = function(x, y) {
         panel.grid(h = -1, v = 2)
         panel.xyplot(x, y)
         panel.loess(x, y, span=1)
       },
       aspect = "xy")
# In these experiment, C is given fixed values from 
#   (7.5,9,12,15,18). We can obtain from the plot that when 
#   C does not change, with the increasement of E, NOx first 
#   increase then decreases. When the value of E is within a 
#   range, NOx increases as C increases.
