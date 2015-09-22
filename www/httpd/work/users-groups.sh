echo "===> Creating users and/or groups."
if ! /usr/sbin/pw groupshow www >/dev/null 2>&1; then 
  echo "Creating group 'www' with gid '80'." 
  /usr/sbin/pw groupadd www -g 80; else echo "Using existing group 'www'."
fi
if ! /usr/sbin/pw usershow www >/dev/null 2>&1; then 
  echo "Creating user 'www' with uid '80'." 
  /usr/sbin/pw useradd www -u 80 -g 80  -c "World Wide Web Owner" -d /nonexistent -s /usr/sbin/nologin 
  else 
echo "Using existing user 'www'." 
fi
