# ProgettoSO
A3. Arduino current meter
   Build a current meter that monitors the power on a line using an arduino and a sensor like this.
   https://docs.rs-online.com/01d5/0900766b81544f27.pdf
   The measure is done by sampling an AC channel where the meter is connected.
   We want to hold:
   -The statistics of the last hour (1 value per min)
   -The statistics of the last day  (1 value per hour)
   -The statistics of the last month days (30 values)
   -The statistics of the last year months (12 values)

   The system should implement a simple interface that allows for
   - setting the "on-line" mode when it writes a sample each x seconds on the serial
   - clearing the statistics
   - querying the statistics
