@echo off
IF [%1] == [] GOTO Error

git add -A
git commit -a -m "%*"
git push

echo COMMIT SUCCESSFULL

GOTO NoError

:Error
echo [ERROR] commit message must be entered

:NoError