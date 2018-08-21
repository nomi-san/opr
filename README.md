# opr

Ram optimizers for all processes, with 5 programming languages for Windows

### Don't ask me 'how it works?', please see [__EmptyWorkingSet__](https://docs.microsoft.com/en-us/windows/desktop/api/psapi/nf-psapi-emptyworkingset) :)

### FAQ (forever alone's questions :))

__Q__: What is loop count 32768?

__A__: _It's max process id in Windows._

<br>

__Q__: Why not multiples of four?

__A__: [__See here__](https://superuser.com/questions/936773/why-are-there-no-odd-windows-process-ids).
Process number always multiples  of four, wait it not true on some versions of Windows and some hidden-system-process numbers is odd.

<br>

__Q__: Why not using EnumProcesses?

__A__: _No ignore any processes while loop counting (else process id < current count, not else =)))._

<br>

__Q__: When run it?

__A__: _Anytime, if you need._

<br>

__Q__: What should use for...?

__A__: _Chromium browser (eg: Chrome, Opera), .NET appliaction .._

<br>

__Q__: Can I run it for only my program?

__A__: _Yes, you can delete loop and change process id to it._

<br>

__Q__: How it works?

__A__: _See code._

<br>

__Q__: I'm not dev or coder?

__A__: _Run executable file._

<br>

__Q__: I don't know 'how to build?'.

__A__: _Run executable file._

<br>

__Q__: I dont't understand anything.

__A__: _Oh!_

<br>

__Q__: Great!

__A__: _Yes!_

<br>

__Q__: Hmmm...

__A__: _Nothing, go back!_

