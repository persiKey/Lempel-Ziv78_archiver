# Lempel-Ziv78 archiver
[:uk:English](#about)

[:ukraine:���������](#���-��������)

 
## About
It is a simple archiver that works as a command line utility.
## How to use
The archiver works only with files located in the current ".\\" folder.

Use a command line interface (cmd, PowerShell, etc.) to access the program's executable file.

One of the following commands is given to the program at the input:

* ### \-\-compress

this command is required to compress a file or files into an archive file. General view of the command:

`*executable file* --compress <name of archive file> <name of file(s) to archive> `

Example:

`.\archive.exe --compress arch.ar a.log test.bmp `
 * ### \-\-decompress

this command unpacks the archive. General view of the command:

`*executable file* --decompress <archive filename>`

Example:

`.\archive.exe --decompress arch.ar`

 ---
 When errors occur, the program displays a corresponding message and terminates work.
## Realization
The implementation uses the algorithm [Lempel-Ziv78](https://math.mit.edu/~goemans/18310S15/lempel-ziv-notes.pdf)

The program has 5 classes:
* The **_CommandInterpreter_** class is responsible for processing the passed arguments and calling the corresponding methods of the _ArchiveManager_ class.
* The **_Validator_** class is used to check the correctness of arguments.
* The **_IArchive_** class is the basic archiver interface that must be implemented in order to use it.
* The **_ArchiveLZ78_** class implements the _IArchive_ interface. This class implements the main algorithm of the program. It works on the section of the file at the bit level.
* The **_ArchiveManager_** class based on the _IArchive_ interface refers to the archiver class. It writes/reads the preamble and controls the archiving process.
## ��� ��������

�� ������� ���������, �� ������ �� ������ ���������� �����.


## ������������

��������� ������ ���� � �������, �� ����������� � ������� �����  ".\\" .

�� ��������� ���������� ���������� ����� (cmd, PowerShell ����) ���������� �� ������������ ����� ��������.

�� ���� ������� �������� ���� � ��������� ������:

*  ### \-\-compress

���� ������� ������� ��� ��������� ����� ��� ����� � �������� ����. ��������� ������ �������:

`*����������� ����* --compress <��'� ��������� ����� ������> <��'� �����/�� ��� ���������> `

���������:

`.\archive.exe --compress arch.ar a.log test.bmp `

  



 * ### \-\-decompress

���� ������� ��������� �����. ��������� ������ �������:

`*����������� ����* --decompress <��'� ����� ������>`

���������:

`.\archive.exe --decompress arch.ar`

 ---
  ��� ��������� ������� �������� �������� �������� ����������� �� ������� ������.

## ���������

� ��������� ����������� �������� [Lempel-Ziv78](https://math.mit.edu/~goemans/18310S15/lempel-ziv-notes.pdf)

�������� �� 5 �����:
* ���� **_CommandInterpreter_** ������� �� ������� ��������� ��������� �� ������ ��������� ������ ����� _ArchiveManager_.
* ���� **_Validator_** ��������������� ��� �������� ���������� ���������.
* ���� **_IArchive_**  � ������� ����������� ����������, �� �� ���� ����������� ��� ������������.
* ���� **_ArchiveLZ78_** ������ ��������� _IArchive_. ��� ���� ������ �������� �������� ��������. ³� ������ �� ������� ����� �� ��� ���. 
* ���� **_ArchiveManager_** �� ����� ���������� _IArchive_ ���������� �� �����-����������.  ³� ������/����� ��������� �� ��������� ������ �����������.
