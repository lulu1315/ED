/******************************************************************************
 * PEL: Predictive Edge Linking
 * 
 * Copyright 2015 Cuneyt Akinlar (cakinlar@anadolu.edu.tr)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************/
#ifndef _TIMER_H_
#define _TIMER_H_

#include <sys/time.h>

class Timer {
private:
  struct timeval start, end;

public:
  Timer(){} //end-TimerClass

  void Start(){
    gettimeofday(&start, NULL);
  } //end-Start

  void Stop(){
    gettimeofday(&end, NULL);
  } //end-Stop

  // Returns time in milliseconds
  double ElapsedTime(){
    if (end.tv_sec == start.tv_sec) return (end.tv_usec - start.tv_usec)/1e3;
    double elapsedTime = 1e6-start.tv_usec;
    elapsedTime += end.tv_usec;
    elapsedTime += 1e6*(end.tv_sec-start.tv_sec-1);

    return elapsedTime/1e3;
  } //end-Elapsed
};

#endif