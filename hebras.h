/*
 * Copyright 2017 <copyright holder> <email>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 */

#ifndef HEBRAS_H
#define HEBRAS_H
#include <unistd.h>
#include <functional>
#include <thread>
#include <condition_variable>
#include <QtGui>
#include "ui_counterDlg.h"


class hebras : public QWidget, public Ui_Counter
{
 Q_OBJECT
private:
  bool parar;
  int num;
  int tiempo;
  
  std::condition_variable cv[4];
  std::mutex cv_m[4];
  std::thread mythread[4];
  

  
public:
  
    hebras();
  
  void run();
  void stop();
  void restart2();
  void cambiarFrecuencia();
  void despertar(int h);

  ~hebras();
  
  public slots:
    void stopTH();
    void restartTH();
    void cambiarFrecuenciaTH();
    
signals:
  void timeout();

  
};

#endif // HEBRAS_H
