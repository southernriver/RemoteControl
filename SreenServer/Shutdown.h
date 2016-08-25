//提权
BOOL EnableShutdownPriv(){
    HANDLE hToken = nullptr;
    TOKEN_PRIVILEGES tkp = {};
    BOOL bRet = FALSE;
    do{
        // Get a token for this process. 
        if (!OpenProcessToken(GetCurrentProcess(),
            TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
            break;
        if (!LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,
            &tkp.Privileges[0].Luid))  break;

        tkp.PrivilegeCount = 1;  // one privilege to set    
        tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

        // Get the shutdown privilege for this process. 

        AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,
            (PTOKEN_PRIVILEGES)NULL, 0);

        if (GetLastError() != ERROR_SUCCESS)
            break;
        bRet = TRUE;
    } while (FALSE);
    if (FALSE == bRet)
        SetLastError(GetLastError());
    if (hToken)
        CloseHandle(hToken);

    return bRet;
}
//重启
BOOL ReSetWindow(DWORD dwFlags, BOOL bForce){
    //提权
    if (EnableShutdownPriv()){
        ExitWindowsEx(dwFlags, bForce);
    }
    return TRUE;
}