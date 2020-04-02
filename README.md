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

* **-file**: It allows you to use a matrix that is saved in a csv file. The file must be separated by ","

## Example

`./Programme -columns 4 -rows 5 -tattoo 01101101`

## Output

The program will generate output by the terminal (standard output) and also in files. The terminal will show:
 
* The original matrix to be encoded

* The EP obtained and the portion of the tattoo used during encoding
 
* The matrices obtained and the tattoo obtained when decoding using both methods

Several files will be created in which it can be viewed. Some will be in csv format and others in txt format (with a
"friendlier" display):
 
* The original matrix (csv and txt)
 
* The matrices decoded by both methods (csv and txt)

* Some intermediate matrices (csv)

