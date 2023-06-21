# Excel Table C++ Console Implementation



## Console interface Excell Table implementation

### Description

This is a C++ Console Interface for opening Table files. 

Each table file has a specific syntax requirement - rows are separated by new lines, cells are separated with the comma symbol ( **,** )

The primary data structure is the Table class. Each table consists of Rows, each row consists of Cells. The supported Cell types, represented in the **"../Cells/"** folder are:

* Integer Cell
* Fraction Cell
* String Cell
* Formula Cell
* Empty Cell

---
### Requirements

Apart from the basic syntax of separating rows with new lines and columns with commas, each cell type has the following requirements for classifying as one:

> A whole number can classify as either an Integer Cell or Fraction Cell

> A decimal point number can classify as Fraction only

> A string must begin and with quotation marks (**"value"**) and each quotation symbol within the string must be preceded by an escape symbol ( **' \\ '**)

> Every formula must begin with an equals sign ( **'='** ). A formula cell can include references to existing cells passed entered as **R#C#** or **r#c#**, where # is an integer. The cell reference **R1C3** references the Cell at the first row, third column. Formulas can hold **literals** as well - constant integer or decimal point numbers. A formula can execute the following operations: **+**, **-**, **\***, **/**, **^**. A formula is represented by a tree-like structure of operations, each operation can be a simple one - just holding a Cell reference or a literal, or a Binary operation, which takes an operant:  **+**, **-**, **\***, **/**, **^** and two other expressions, where the expressions can be either simple or binary. Each binary expression must be surrounded with brackets. 

>Example valid function cell syntax: __= (((R4C1+10)*2)+R5C2)__

---
### Formula Cell References Evaluation:

* Integer Cells are evaluated with the value they hold
* Fraction Cells are evaluated with the value they hold
* String Cells are __converted to an integer or double if the value they hold can be parsed to the corresponding type__. Otherwise they are evaluated as 0
* Empty cells are evaluated as 0
* Non-existing cells are evaluated as 0

---
### Supported Commands
> open --- takes a file name and creates a table with its values

> print --- prints the Table with formula cells evaluated

> edit --- takes a cell location and new value

> save --- saves the changes to the opened file

> save as --- takes a file name and creates and saves the changes to the opened file there

> close --- closes the opened file

> exit

---
### Example 
The file __example.txt__ has the following data:
```
10,"hey",,123.65
"\"Quoted\"",,"hey hey hey"
12.3,,4
1,2,= ((r3c3*r4c2)+2),3,4
= (((R4C1+10)*2)+R5C2),4
```
Opening:
```
open example.txt
Table opened successfully!
print
>example.txt

___________________________________
|10      |hey|           |123.65|  |
|________|___|___________|______|__|
|"Quoted"|   |hey hey hey|      |  |
|________|___|___________|______|__|
|12.3    |   |4          |      |  |
|________|___|___________|______|__|
|1       |2  |10         |3     |4 |
|________|___|___________|______|__|
|26      |4  |           |      |  |
|________|___|___________|______|__|

```
Extending table:
```
edit r7c2 "table extension"
Cell edited successfully
print
>example.txt

_______________________________________________
|10      |hey            |           |123.65|  |
|________|_______________|___________|______|__|
|"Quoted"|               |hey hey hey|      |  |
|________|_______________|___________|______|__|
|12.3    |               |4          |      |  |
|________|_______________|___________|______|__|
|1       |2              |10         |3     |4 |
|________|_______________|___________|______|__|
|26      |4              |           |      |  |
|________|_______________|___________|______|__|
|        |               |           |      |  |
|________|_______________|___________|______|__|
|        |table extension|           |      |  |
|________|_______________|___________|______|__|
```
Adding new cell, note that the function cell that references R4C2 also changes:
```
edit r4c2 -3
Cell edited successfully
print
>example.txt

_______________________________________________
|10      |hey            |           |123.65|  |
|________|_______________|___________|______|__|
|"Quoted"|               |hey hey hey|      |  |
|________|_______________|___________|______|__|
|12.3    |               |4          |      |  |
|________|_______________|___________|______|__|
|1       |-3             |-10        |3     |4 |
|________|_______________|___________|______|__|
|26      |4              |           |      |  |
|________|_______________|___________|______|__|
|        |               |           |      |  |
|________|_______________|___________|______|__|
|        |table extension|           |      |  |
|________|_______________|___________|______|__|

```
