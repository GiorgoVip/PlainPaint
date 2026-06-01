##-   UPDATE ONLINE PROJECT   -##

#// PlainPaint_PAT01	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

#// git rm (--cached) <file> then commit			#// be carefull and have backups
echo "GIT: username:"
git config user.name "GiorgoVip" ; git config user.name

echo "GIT: email:"
git config user.email

##########################
##########################


#git config remote.origin.url git@github.com:GiorgoVip/PlainPaint.git

git branch -M main

##########################
git add --all

git status


echo "Commit comment: "
read commit

git commit -m $commit


git push -u origin main --force


git config --local credential.helper cache
