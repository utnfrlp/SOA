# Parallelized Oscillatory-Sort Algorithm
#### by Jorge R. Podjarny

This algorithm is a <a href="https://en.wikipedia.org/wiki/Bubble_sort">Bubble Sort</a> variation with parallelization factibility.
Was published in 1981.

The idea is to program it at low level, using *compare()* and *swap()* GPU
processing primitives. GPU also allows more execution lines at the same
time than using CPU.

To program the *control_thread()* function, the
*search_zero_in_a_bits_vector()* primitive function probably can be used.


## The proposal

Given a n-positions vector with data to order, make N-1 threads.

If N is odd, add the element at the end with FFFF value that guarantee that
it is always the highest.

Make a *is_finished* bits vector to keep every thread status, and know if the
thread is active (1, true) or not (0, false).

When every thread is finished, the *parallelized_oscillatory_sort_algorithm()* is over.

Every thread has assigned two vector positions.

<p align="center">
  <img src="https://user-images.githubusercontent.com/7065401/28588255-5aefedae-7150-11e7-8d9c-c3b4bc98cebc.png">
</p>

## Pseudocode

### initialization()

	// Init all threads.
	for (every_thread_index T) do
		is_finished[T] = 0
---


### first_odd_thread_pseudocode()
thread index == 1, special case

	is_finished[T] = 0
	is_ordered = check_order()

	if (!is_ordered)
		swap()
		wake(thread T+1)
		wait_till(is_finished[T+1] = 0)

	is_finished[T] = 1
	sleep(T)
---


### odd_thread_pseudocode()
thread index > 0

	is_finished[T] = 0  // begin
	is_ordered = check_order()

	if (!is_ordered)
		swap()
		wake(thread T-1)
		wake(thread T+1)
		wait_till(is_finished[T-1] = 0)
		wait_till(is_finished[T+1] = 0)

	is_finished[T] = 1
	sleep(T)
---


### even_thread_pseudocode()

	is_finished[T] = 0

	// Wait till both parent threads are finished, to guarantee every EVEN thread
	// is executed at least 1 time and are synchronized.
	// There could be another better synchronization tool.
	wait_till(is_finished[T-1] = 1)
	wait_till(is_finished[T+1] = 1)

	is_ordered = check_order()

	if (!is_ordered)
		swap()
		wake(thread T-1)
		wake(thread T+1)
		wait_till(is_finished[T-1] = 0)
		wait_till(is_finished[T+1] = 0)

	is_finished[T] = 1
	sleep(T)
---


### control_thread_pseudocode()

	// Check if the whole 'is_finished' vector is true (1).
	// This could be done with a built-in primitive that seeks a false (0) value,
	// and return false if the whole vector has true (1) values.
	all_true = true

	for (every_thread_index T) do
		if (is_finished[T] == 0)
			all_true = false

	if (all_true == true)
		finish_sort()  // end
---
