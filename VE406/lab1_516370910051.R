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
gradebook.df = data.frame(
  
  fail = c(rep(FALSE,14), TRUE, rep(FALSE,25)),
  gender = c(rep("Female",20), rep("Male",20)),
  proj = c(rep(18,6),rep(17,4), rep(16,3), rep(15,7), rep(18,5),
          rep(17,4), rep(16,5), rep(15,6))
)


# Task 3 part(b) --------------------------------------------

# Task 3 part(c) --------------------------------------------

# Task 3 part(d) --------------------------------------------

# Task 4 part(a) --------------------------------------------

# Task 4 part(b) --------------------------------------------

# Task 4 part(c) --------------------------------------------

# Task 5 part(a) --------------------------------------------

# Task 5 part(b) --------------------------------------------

# Task 5 part(c) --------------------------------------------

# Task 6 part(a) --------------------------------------------

# Task 6 part(b) --------------------------------------------

# Task 6 part(c) --------------------------------------------

# Task 6 part(d) --------------------------------------------

# Task 7 ----------------------------------------------------
