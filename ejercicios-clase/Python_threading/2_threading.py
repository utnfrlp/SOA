#!/usr/bin/python
import threading
import time

class myThread (threading.Thread):
   def __init__(self, threadID, name, counter):
      threading.Thread.__init__(self)
      self.threadID = threadID
      self.name = name
      self.counter = counter

   def run(self):
      print('Starting ' + self.name)

      # tomar el lock para sincronizar threads
      threadLock.acquire()
      print_time(self.name, self.counter, 3)

      # liberar lock para permitir la ejecución del próximo thread
      threadLock.release()

      print('Exiting ' + self.name)


def print_time(threadName, delay, counter):
   while counter:
      time.sleep(delay)

      print(threadName)
      counter -= 1


threadLock = threading.Lock()
threads = []

# crear nuevos threads
thread1 = myThread(1, 'Thread-1', 1)
thread2 = myThread(2, 'Thread-2', 2)

# comenzar cada thread
thread1.start()
thread2.start()

# agregar cada thread a una lista
threads.append(thread1)
threads.append(thread2)

# esperara a que terminen todos los threads
for t in threads:
    t.join()

print('Exiting Main Thread')
