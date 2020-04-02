# dataProtectionProject

## Setup

1. Run: `make`
2. Run `./Programme`

It is necessary to have GMP installed with support for c and c ++.

## Parameters

The program allows a series of parameters. The flags to be used are listed below.

* **-columns**: It allows you to set the number of columns in the matrix. It must be a value greater than 1.

* **-rows**: It allows you to set the number of rows in the matrix. It must be a value greater than 1.

* **-column_1**: It allows you to set column 1 of the matrix that will be used for the encoding. It must be a value greater
 than or equal to 0.
 
* **-column_2**: It allows you to set column 2 of the matrix that will be used for the encoding. It must be a value greater 
than or equal to 0.

* **-tattoo**: It allows you to set the tattoo to apply during the encoding. It must be a binary number with a maximum 
size of 128 bits

* **-ks**: It allows you to set the key that will be used to generate r2. It must be a positive number

* **-process**: It allows you to specify the type of process you want to execute (encoding, decoding or both). 
The value should be "e", "d" or "ed".

* **-file**: It allows you to use a matrix that is saved in a csv file. The file must be separated by ",". If you are 
executing a decoding process, this parameter is mandatory. If you are decoding and you are using the file generated
with the encoding process, then you have to use "encoded_with_tattoo.csv".

* **-EP**: It allows you to indicate the EP value. It will be used only if it is a decoding process. It is mandatory if
you are decoding.

* **-p**: It allows you to indicate the p value. If you are decoding it is mandatory.

* **-q**: It allows you to indicate the q value. If you are decoding it is mandatory.




## Example

`./Programme -columns 4 -rows 5 -tattoo 01101101`

## Output

The program will generate output by the terminal (standard output) and also in files. The terminal will show:
 
* The original matrix to be encoded

* The values of p, q and the encoding columns used

* The EP obtained and the portion of the tattoo used during encoding
 
* The matrices obtained and the tattoo obtained when decoding using both methods

Several files will be created in which it can be viewed. Some will be in csv format and others in txt format (with a
"friendlier" display):
 
* The original matrix (csv and txt)
 
* The matrices decoded by both methods (csv and txt)

* Some intermediate matrices (csv)

## Clarifications

* You can run  `sh compare.sh` to check if the decoded matrices are the same as the original. The file is a bash 
script that runs two diff commands comparing the file "original.csv" with the files "decoded_3_3_1.csv" and "decoded_3_3_2.csv"

* We could not perform all the tests so there could be certain bugs / errors for certain cases (for example with the
data passed as parameters when executing the program). However, we believe that there should be no problem using
the defaults values (`./Programme`)
