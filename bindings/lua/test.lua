-- load opr
opr = require('opr')

-- specific process id
pid = 123
ret = opr.Clean(pid)
print(string.format('process [%d]: %s',
	pid, ret == 1 and 'ok' or (ret == -1 and 'cannot access or does not exist' or 'fail')))

-- specific process name
pname = 'example.exe'
ret = opr.Clean(pname)
print(string.format('process "%s": %s',
	pname, ret == 1 and 'ok' or (ret == -1 and 'cannot access or does not exist' or 'fail')))

-- all process
ret = opr.CleanAll()
print(string.format('%d %s cleaned',
	ret, ret < 2 and 'process is' or 'processes are'))