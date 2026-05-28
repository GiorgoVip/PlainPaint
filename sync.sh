##-   SYNCRONIZE WITH THE ONLINE PROJECT   -##



#// git rm (--cached) <file> then commit			#// be carefull and have backups
echo "GIT: username:"
git config user.name

echo "GIT: email:"
git config user.email

##########################
##########################


#git remote add origin https://try.gogs.io/Giorgo/rasdr.git #// reset with git config remote.origin.url (<url>)

git branch -M main

##########################
#git fetch origin

git pull origin



git status
