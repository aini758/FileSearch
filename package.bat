@echo off

set dir_curr=%cd%
echo #==================================================================
echo ��ǰĿ¼��%dir_curr%
echo #==================================================================

cd bin

set /p dir_clear=������Qt�������windeployqt.exeĿ¼������C:\Qt\Qt5.7.1\5.7\msvc2013\bin����

if not exist "%dir_clear%" (
    echo �����Ŀ¼�����ڣ�%dir_clear%
    goto bat_ended
)
:end_input

:package_begin

echo ��ʼִ�д��������
echo #==================================================================
%dir_clear%\windeployqt.exe FileSearch.exe
echo #==================================================================
echo ���������
ls -ltr
:package_ended

:bat_ended
echo #==================================================================
pause