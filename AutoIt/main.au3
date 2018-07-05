For $i = 0 to 32768 step 4
	Local $handle = DllCall('kernel32.dll', 'handle', 'OpenProcess', 'dword', 0x1F0FFF, 'bool', 0, 'dword', $i)
	If Not @error Then
		$handle = $handle[0]
		DllCall('kernel32.dll', 'bool', 'SetProcessWorkingSetSizeEx', 'handle', $handle, 'int', -1, 'int', -1, 'dword', 0x1)
		DllCall('psapi.dll', 'bool', 'EmptyWorkingSet', 'handle', $handle)
		DllCall('kernel32.dll', 'bool', 'CloseHandle', 'handle', $handle)
	EndIf
Next
