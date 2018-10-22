# Task 1 part(a) --------------------------------------------
deb.df = read.table("debonding.txt", header = T)
str(deb.df)
# read.table may be very slow in practice, because it will
#   evaluate data while reading it. We may use other function
#   in R to read large quantity of data.


# Task 1 part(b) --------------------------------------------
deb.full.LM = lm(debonding ~ time + voltage + ph + temp, 
                 data = deb.df)
summary(deb.full.LM)
# debonding = -96.51 + 0.063 time + 0.0016 voltage - 0.27 ph 
#             + 0.33 temp


# Task 1 part(c) --------------------------------------------
summary(deb.full.LM)$r.square


# Task 1 part(d) --------------------------------------------
plot(fitted.values(deb.full.LM), rstandard(deb.full.LM), 
     xlab = "Fitted value", ylab = "Standartd residual")


# Task 1 part(e) --------------------------------------------
plot(deb.full.LM$residuals[-length(deb.full.LM$residuals)], 
     deb.full.LM$residuals[-1], xlab = "Previous", 
     ylab = "Residual")


# Task 1 part(f) --------------------------------------------
acf(deb.full.LM$residuals)


# Task 1 part(g) --------------------------------------------
qqnorm(deb.full.LM$residuals, xlab = "N(0,1)", ylab = "Residual")
qqline(deb.full.LM$residuals)


# Task 1 part(h) --------------------------------------------
qqnorm(rstandard(deb.full.LM), xlab = "N(0,1)", 
       ylab = "Standard Residual")
qqline(rstandard(deb.full.LM))
# Difference between (g) & (h)
#   

# Task 1 part(i) --------------------------------------------
# library(MASS)
# debonding.dc = boxcox(deb.full.LM)
# By boxcox() in MASS we find an appropriate lambda = 0.5
lambda = 0.5
debonding.bc = (deb.df[,"debonding"] ^ lambda- 1) / lambda
debonding.bc


# Task 1 part(j) --------------------------------------------
debonding.full.bc.LM = lm(debonding.bc ~ time + voltage + ph + temp, 
                          data = deb.df)
summary(debonding.full.bc.LM)
# debonding.bc = -3.899e+01 + 2.775e-02 time + 6.419e-04 voltage  
#                 -1.305e-01 ph + 1.347e-01 temp
# No, there is no evidence that this model is better.



# Task 1 part(k) --------------------------------------------


# Task 1 part(l) --------------------------------------------

# Task 1 part(m) --------------------------------------------
deb.co = summary(deb.full.LM)
b1.ci = deb.co$coefficients[2,1] + c(-1, 1) * 
  deb.co$coefficients[2,2] * qt(0.975, deb.full.LM$df.residual)
b1.ci


# Task 1 part(n) --------------------------------------------
predict.df = data.frame(time = 30.00, voltage = 1350, ph = 4.00,
                        temp = 300)
predict(deb.full.LM, predict.df, interval = "confidence")


# Task 1 part(o) --------------------------------------------
predict(deb.full.LM, predict.df, interval = "prediction")


# Task 1 part(p) --------------------------------------------
deb.no.v.LM = lm(debonding ~ time + ph + temp, data = deb.df)
deb.no.v.p.LM = lm(debonding ~ time + temp, data = deb.df)
summary(deb.no.v.LM)
summary(deb.no.v.p.LM)
# Judging from adjusted R-square, deb.no.v.LM is better. We
#   cannot use this value to compare debonding.full.bc.LM with
#   the others, because its response is different.
# If we have model 5: Y~1+., we can use R-square to compare it
#   with model 1.


# Task 2 part(a) --------------------------------------------
sim.df = read.csv("sim_lab2.csv.bz2")
sim.LM = lm(y ~ . + x1 * x3 + x1 * x4 + x2 * x3 + x2 * x4 + 
              x3 * x4, data = sim.df)
summary(sim.LM)
# In summary(), x3c:x4c and x3d:x4c are NA. That is because 
#   there exists no data that have x3 = c(c,d), x4 = C at the 
#   same time.


# Task 2 part(b) --------------------------------------------



# Task 2 part(c) --------------------------------------------
# P-value is the indicator of correctness of original hypothesis.
# Having a large p-value output means the assumption of
#   relation betweenthe specific item and y may be wrong.


# Task 2 part(d) --------------------------------------------
source ("lab2_func.R")
f.vec = replicate(1e4, sim.p.func(n= 200))
sim.plot()
