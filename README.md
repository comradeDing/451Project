# 451Project
Final project for CSci 451: Operating Systems

**_Steps to build and run program..._**

## BUILDING AND RUNNING PRODUCERS:
First, you need to build the producer programs. If you wish to modify what the producers output,
you would do so at this time. Change the rules of the loop to do this.
Run these commands in the working directory to build then run the producers.
```
	~ $ make buildprods
	~ $ make runprods
```
To kill the producer processes, use ctrl + c in the bash terminal, and run a 'ps' command to check
if any producer processes didn't get killed. If they are still running, run a 'kill <pid>' command.
	
## BUILDING AND RUNNING CONSUMER:
To build and run the consumer, you need to open another terminal, and run the following commands in
the working directory:
```
	~ $ make buildcons
	~ $ make runcons
```
The consumers can only run if the producers are running. If not, you will probably get a segmentation
fault or an error message from sem_open(2). To kill the consumer process, you can enter 'q' into the
terminal running the consumer process, or use 'ctrl + c'. It's recomended to enter 'q' to cleanly end
the process.
