# Task 1 part(a) --------------------------------------------
deb.df = read.table("debonding.txt", header = T)
str(deb.df)


# Task 1 part(b) --------------------------------------------
deb.full.LM = lm(debonding ~., data = deb.df)
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


# Task 1 part(i) --------------------------------------------
library(MASS)
boxcox(deb.full.LM)
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
# The F-statistic is testing overall significance. It is testing the
#   assumption. In this case we cannot tell which model is better 
#   from F-test.



# Task 1 part(k) --------------------------------------------
# The p-value of F-statistic in these two models are both 
#   smaller than 0.05. Therefore, we can reject the null 
#   hypothesis that debonding is not related to any of the 
#   variables.


# Task 1 part(l) --------------------------------------------
# The p-value (alpha) of ph shows it is less significant than
#   the other three regressors, so its slope may be zero.


# Task 1 part(m) --------------------------------------------
b1.ci = confint(deb.full.LM, "time", level = 0.95)
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


# Task 2 part(a) --------------------------------------------
sim.df = read.csv("sim_lab2.csv.bz2")
sim.LM = lm(y ~ . + x1 * x3 + x1 * x4 + x2 * x3 + x2 * x4 + 
              x3 * x4, data = sim.df)
summary(sim.LM)
# In summary(), x3c:x4c and x3d:x4c are NA. That is because 
#   there exists no data that have x3 = c(c,d), x4 = C at the 
#   same time.


# Task 2 part(b) --------------------------------------------
# sim.x4.B.df = sim.df
# sim.x4.B.df$x4 = relevel(sim.x4.B.df$x4, ref = "B")
# sim.x4.B.LM = lm(y ~ . + x1 * x3 + x1 * x4 + x2 * x3 + 
#               x2 * x4 + x3 * x4, data = sim.x4.B.df)
# No. From this operation we will find there is no significant
#   difference whether we take B or C for x4.


# Task 2 part(c) --------------------------------------------
anova(sim.LM)
# A common practice to select variables.
# P-value is the indicator of correctness of original hypothesis.
# Having a large p-value output means the assumption of
#   relation between the specific item and y may be wrong.
# The test value of x3:x4 is too large, it means we can drop 
#   this item.


# Task 2 part(d) --------------------------------------------
source ("lab2_func.R")
f.vec = replicate(1e4, sim.p.func(n = 200))
sim.plot()
# This function gives an example that even if in 1e4 times of 
#   sampling whter most of the p-values are very small, it 
#   cannot unsure the correctness of model.
# Therefore, a F-test without examing residuals first will be 
#   nonsense.