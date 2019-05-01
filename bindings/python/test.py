# import opr
from opr import opr

if __name__ == '__main__':
	# specific process id
	pid = 123
	ret = opr.Clean(pid)
	print(('process [{0}]: {1}').format(
		pid, 'ok' if (ret == 1) else ('cannot access or does not exist' if (ret == -1) else 'fail')))

	# specific process name
	pname = 'garena.exe'
	ret = opr.Clean(pname)
	print(('process "{0}": {1}').format(
		pname, 'ok' if (ret == 1) else ('cannot access or does not exist' if (ret == -1) else 'fail')))

	# all process
	ret = opr.CleanAll()
	print(('{0} {1} cleaned').format(
		ret, 'process is' if (ret < 2) else 'processes are'))
