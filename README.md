ZOS C++ Programming Test 2.3.0

## Total Time Spent:
  - From 2020.12.10 - 13:21
  - Till: 2020.12.10 - 17:55
  
  Total #1: 4 hours, 34 minutes
  
  - From 2020.12.11 - 09:28
  - Till 2020.12.11 - 11:44
  
  Total #2: UNKNOWN
  
  Overall Time = 
  
# Workflow(In order):

## I. Tried enabling /permissive- to check for any additional compile errors
<br>
  
## II. Wondered why nothing is random, and if it should or shouldn't be random, but turns out that I am not to modify the input values?
  - Do not modify the existing four command line input parameters used.  Feel free to add additional command line
      inputs if needed, but make sure they are not required.
<br>
  
## III. Performance:<br>
  Check for "new" and "delete" oprerators, common mistake when programmers forget about that:
  <br>
These two seem fine to me:
   - m_position = new float[3]; is being handled correctly, because the destructor takes care of it
   - ObjectManager since we are calling a new ObjectManager(), that means we its memory gets deallocated when ObjectManager::~ObjectManager() gets called, meaning that we have a wrapper for this which takes care of memory allocation for us, I think.
<br>

These two seem skethcy performance wise:
   - WorkerThread is never being deleted, which makes me wonder if its good or not 
   - m_objects seems sketchy, might not be correct!

Went on with Performance issues and found that ppl use profilers for performance checking:
<br>

Sources:
   - https://stackoverflow.com/questions/1515688/how-to-find-performance-bottlenecks-in-c-code
   - https://stackoverflow.com/questions/375913/how-can-i-profile-c-code-running-on-linux/378024#378024
<br>

Found this tool to work with:
   - http://www.codersnotes.com/sleepy/

Conclusion: Tried using it but I had no idea what I was doing so I just stopped and put my focus elsewhere.

Found that Mines aren't getting destructed, nor being deleted, which means they dont get destroyed at all
Answer might be because they aren't even activated whatsoever, which I couldn't for the life of me figure out why its like that.
<br>
<br>

## IV. Error Handling:<br>
Error handling could be used for: when there aren't new mines generated, lets not proceed then
<br>

## V. SetActive():<br>
Spent quite a bit of time on figuring out why mines aren't set to active, still unsure why not

## VI. Custom Feature:<br>

S-Z: If at least two enemy mines are destroyed, that same team gets to explode another of its mines. The team
     can continue to explode mines until less than two enemy mines are destroyed when exploding one of their mines.
     
## VII. What Else I Would Have Done:
1. If statements should be used with an else so every time something we dont want to happen, we at least know its happening. Minimally displaying some kind of cout so we are aware of the issue

2. Check through all of the cases we use thew "new" operator so no matter what "delete" operator gets called after we are done using the object, in all cases. Otherwise we are losing performance, leaking memory
