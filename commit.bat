IF [%1] == [] GOTO Error

git add -A
git commit -a -m "%*"
git push

:Error
echo [ERROR] commit message must be entered