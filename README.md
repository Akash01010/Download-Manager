# Download-Manager
Basic internet download manager to download a file in pieces parallelly and merging them back to original one.
The file will be downloaded in the same folder where the code is.

Steps:
Step1: Compile the file and make an executable.
Step2: ./a.out <url of the file>  <approx size of file> <no of parallel downloads you want to make> <file name you want to download with>
Example: ./a.out http://10.8.19.24/ProxyData/access.log-20161108.gz  1500000000 2 file3.gz
