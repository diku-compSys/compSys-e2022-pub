# Exercises

## Scalability and speedup

### Amdahl's Law

For this question we use Amdahl's Law to estimate speedup in latency.
Suppose we have a program where 4% of the work is *not*
parallelisable.  Assuming the rest can be fully parallelised without
any overhead:

1. What is the speedup if we run it on a 4-processor machine?
2. What about with 128 processors?
3. What is the smallest number of processors that will give us a speedup of at least 5?
4. What is the smallest number of processors that will give us a speedup of at least 30?

<details>
  <summary>Open this to see the answer</summary>

Since 4% is not parallelisable, *p=0.96*, which gives us *S(N) =
1/(1-0.96+(0.96/N))*.

1. *S(4) = 1 / (1-0.96+(0.96/4)) = 3.57*

2. *S(128) = 1 / (1-0.96+(0.96/128)) = 21.05*

3. *S(N) = 5*.  Solving for *N*, we get *N=6*.

4. Since the limit of *S(N)* is *25* as *N* goes to infinity, we
   cannot ever get a speedup of at least 30 with this program.

</details>

### Gustafson's Law

For this question we use Gustafson's Law to estimate speedup in latency.  Suppose
we have a program where 4% of the work is *not* parallelisable.
Assuming the rest can be fully parallelised without any overhead, and
that the parallel workload is proportional to the amount of
processors/threads we use:

1. What is the speedup if we run it on a 4-processor machine?
2. What about with 128 processors?
3. What is the smallest number of processors that will give us a speedup of at least 5?
4. What is the smallest number of processors that will give us a speedup of at least 30?

<details>
  <summary>Open this to see the answer</summary>

Since 4% is not parallelisable, *s=0.04*, which gives us *S(N) =
N + (1-N) * 0.04*.

1. *S(4) = 3.88*

2. *S(128) = = 122.92*

3. *S(N) = 5*.  Solving for *N*, we get *N=31/6*, and since we cannot
   have a fractional number of processors, we round up to *N=6*.

4. *S(N) = 30*.  Solving for *N*, we get *N=749/24*, which we round up
   to *N=32*.

</details>

### Estimating parallel fraction

Suppose that a program runs in *50s* on one processor (*N=1*) and in
*10s* on sixteen processors (*N=16*) with the same workload.  Assuming
that the parallel part of the program scales linearly with the number
of processors used, what is the parallelisable fraction *p*?

<details>
  <summary>Open this to see the answer</summary>

Since the workload is fixed, we use Amdahl's law.  The speedup is
*50/10=5* for *N=16*, which we plug into the formula and get the
following equation:

*1/((1-p)+(p/16)) = 5*

Solving for *p*, we get *p=65/75*, or *p ~ 0.86*.

</details>

### Performance comparisons

Suppose you wish to parallelise an image processing algorithm.  You
are given an efficient *sequential* implementation *I_s*, and you then
develop a parallel implementation *I_p*.  You have access to two
machines:

1. A machine with a single very fast processor running at 4GHz (i.e. executes 4
   billion instructions per second).

2. A machine with eight slower processors, each running at 2.5GHz
   (i.e. each executes 2.5 billion instructions per second).

Explain how you could perform a fair performance comparison of *I_s*
and *I_p*.

<details>
  <summary>Open this to see the answer</summary>

When we compare the performance of two programs, both must be shown in
their best light.  *I_s* cannot take advantage of more than one
processor, so it would be unfair to use a single one of the slow
processors.  Conversely, parallel programs like *I_p* might not run
optimally on a single processor.  Thus, we need to run *I_s* on system
1 and *I_p* on system 2 and compare their performance.  Since the
systems are different, we cannot use speedup-in-latency.  What we need
to do is compute the *throughput* of the two programs, and then we can
compute the speedup-in-throughput.
</details>

## Exercises from COD

* 6.3

* 6.8
