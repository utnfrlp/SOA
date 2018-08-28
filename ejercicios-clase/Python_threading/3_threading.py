#!/usr/bin/python
import queue
import threading
import time

exitFlag = 0

class myThread (threading.Thread):
   def __init__(self, threadID, name, q):
      threading.Thread.__init__(self)
      self.threadID = threadID
      self.name = name
      self.q = q

   def run(self):
      print('Starting ' + self.name)
      process_data(self.name, self.q)
      print('Exiting ' + self.name)


def process_data(threadName, q):
    while not exitFlag:
        # queueLock.acquire()

        if not workQueue.empty():
            data = q.get() # toma elemento de la cola
            # queueLock.release()
            print('{} processing {}'.format(threadName, data))
            time.sleep(1)
        else:
            # queueLock.release()
            time.sleep(1)


threadList = ["Thread-1", "Thread-2", "Thread-3"]
nameList = ["One", "Two", "Three", "Four", "Five"]
queueLock = threading.Lock()
workQueue = queue.Queue(5)
threads = []
threadID = 1

# crear nuevos threads
for tName in threadList:
   thread = myThread(threadID, tName, workQueue)
   thread.start()
   threads.append(thread)
   threadID += 1

# completar la cola
queueLock.acquire()
print('Filling queue')
time.sleep(1)

for word in nameList:
   workQueue.put(word)
queueLock.release()

# esperar a que la cola quede vacía
while not workQueue.empty():
    pass

# notificar a los threads que deben terminar
exitFlag = 1

# esperara a que terminen todos los threads
for t in threads:
   t.join()

print('Exiting Main Thread')
