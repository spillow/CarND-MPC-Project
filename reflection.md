# Reflections

---

## The Model

The goal of model predictive control is to formulate a kinematic or dynamic model that predicts the motion of the car
a short interval into the future and treats control as an optimization problem over quantities such as cross track error.
The result will be a time series of actuation controls (here, steering angle and acceleration) to navigate the car along
the desired path.

In terms of a full processing pipeline, MPC will receive position and heading via, say, a particle filter
approach and a collection of way points from a path planning module that the car should traverse.

We treat the state of the car as a 6-element vector:

* x - the x position of the car
* y - the y position of the car
* psi - the heading of the car
* v - the speed of the car
* cte - the cross track error (i.e., deviation from the desired location)
* epsi - the error in the heading from the desired heading

A simple kinematic model of motion is used that evolves these parameters over time.  The only notable parameter in this model
that would be specific to a given car is L<sub>f</sub> which measures the length of the car from its front to its center of gravity.

## Timestep Length and Elapsed Duration (N & dt)

The model ultimately settled on values of N = 15 (the number of timesteps) and dt = 0.05 s (interval between timesteps).  An initial value of N = 25 (so, 1.25 seconds) was used but was too large
due to the latter predicted points influencing the optimization too much.  N = 10 seemed to not predict far enough to upcoming curves.
Given that the issued actuator commands have a 100 ms latency, we must have a dt no greater than 0.1.  Halving that produced good results.

## Model Predictive Control with Latency

Without taking into account the 100 ms latency of commands, the car tends to oscillate and veer off course since, by the time the actuations
actually occur, the car is in a different state from when it decided that those would be good actuations to perform.

When new position, heading, and velocity information come in, we use the kinematic model to predict our position 100 ms in the future and pass that as the
initial state to our solver.  By issuing the solved for steering angle and acceleration now, it would then happen 100 ms later which is when we predicted
it would be a good time to use those values.

