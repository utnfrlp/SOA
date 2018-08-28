import threading
from queue import Queue


def creator():
    """
    Creates data to be consumed and waits for the consumer
    to finish processing
    """
    print('Creating data and putting it on the queue \n')
    for item in data:
        evt = threading.Event()
        q.put((item, evt))

        print('(1) Waiting for data to be doubled')
        evt.wait()

    finish = True
    print('(1) END')

def my_consumer():
    """
    Consumes some data and works on it

    In this case, all it does is double the input
    """
    while thread_one.is_alive():
        try:
            item, evt = q.get(block=True, timeout=1)

            print('(2) item found to be processed: {}'.format(item))
            processed = item * 2
            print('(2) processed item: {} \n'.format(processed))
            evt.set()
            q.task_done()
        except Exception:
            print('(2) END')


if __name__ == '__main__':
    q = Queue()
    data = [5, 10, 13, -1]
    finish = False
    thread_one = threading.Thread(target=creator)
    thread_two = threading.Thread(target=my_consumer)
    thread_one.start()
    thread_two.start()

    q.join()
