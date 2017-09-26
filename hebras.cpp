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

#include "hebras.h"

hebras::hebras(): Ui_Counter()
{
  
  
  parar=false;
  num=0;
  tiempo=500000;
 
  
  setupUi(this);
  verticalSlider->setMinimum(1);
  verticalSlider->setMaximum(16);
  verticalSlider->setValue(verticalSlider->maximum()/2);
  lcdNumber_F->display(verticalSlider->value());
  show();
  
  
  connect(button, SIGNAL(clicked()),this,SLOT(stopTH()));
  connect(restart, SIGNAL(clicked()),this,SLOT(restartTH()));
  connect(verticalSlider, SIGNAL(sliderMoved(int)),this,SLOT(cambiarFrecuenciaTH()));
  connect(verticalSlider, SIGNAL(actionTriggered(int)),this,SLOT(cambiarFrecuenciaTH()));
  
  
  mythread[0] = std::move(std::thread(&hebras::run,this));
  mythread[1] = std::move(std::thread(&hebras::stop, this));
  mythread[2] = std::move(std::thread(&hebras::restart2, this));
  mythread[3] = std::move(std::thread(&hebras::cambiarFrecuencia, this));
 
}


void hebras::run()
{
  std::unique_lock<std::mutex> lk(cv_m[0]);
  
  while(true)
  {
     
    if(parar)
      cv[0].wait(lk);
  
    std::lock(cv_m[1],cv_m[2],cv_m[3]);
   
    num++; 
    lcdNumber->display(num);
    
   lk.unlock();
   
    cv_m[1].unlock();
    cv_m[2].unlock();
    cv_m[3].unlock();
    
     
   std::this_thread::sleep_for(std::chrono::microseconds(tiempo));
   
   lk.lock();
  }
    
   
}

void hebras::stop()
{

  std::unique_lock<std::mutex> lk(cv_m[1]);
  
  
  while(true){
 
     
     cv[1].wait(lk); 
     
     
    
     if(!parar){
      parar=true;
      button->setText("START");
    }
    else{
      cv_m[0].lock(); 
      parar=false;
      button->setText("STOP"); 
     
      
      cv_m[0].unlock();
    
      cv[0].notify_one();
      
    }
  
  }
}

void hebras::restart2()
{
  
   std::unique_lock<std::mutex> lk(cv_m[2]);
  
  while(true){
    
    
     
    cv[2].wait(lk); 
   
    cv_m[0].lock();
    
    num=0;
    lcdNumber->display(num);
     
    
    cv_m[0].unlock();
    
  }
}

void hebras::cambiarFrecuencia()
{
  int f;
    std::unique_lock<std::mutex> lk(cv_m[3]);
    
  while(true){
    
    
     
    cv[3].wait(lk); 
   
    
    cv_m[0].lock();
    
    f=verticalSlider->value();
    tiempo=4000000/f;
    lcdNumber_F->display(f);
    
    
    cv_m[0].unlock();
    

   
  }
  
  
  
  
}

void hebras::despertar(int h)
{
  cv[h].notify_one();
  
}



hebras::~hebras(){
  
    mythread[0].detach();
    mythread[1].detach();
    mythread[2].detach();
    mythread[3].detach();
  
}



void hebras::stopTH()
{
  despertar(1);
}

void hebras::cambiarFrecuenciaTH()
{
  despertar(3);
}

void hebras::restartTH()
{
  despertar(2);
}














