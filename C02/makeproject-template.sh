# !/bin/bash

#<<<< INSERT PLEDGE HERE

# This sets up the entire project starting with the tar file.
# Extracts and moves all contents into ./files/
# creates the compile, run and clean scripts inside ./files/
# when called, checks if files/snapshot exists and if it exists, 
# archives it; then it checks if ./files/ exists,
# and if yes, packages everything into a tarfile and archives it
# and creates a new ./files/ folder as described above (i.e. fresh start)

#<<<< INSERT SCRIPT HERE

# Create the helper scripts inside ./files/
# see writeup for details.

compilescript=./files/compile.sh
runscript=./files/run.sh
snapshotscript=./files/make-snapshot.sh

cat << 'EOF' > $compilescript 
#<<<< INSERT SCRIPT HERE
EOF

cat << 'EOF' > $runscript
#<<<< INSERT SCRIPT HERE
EOF

cat << 'EOF' > $snapshotscript
#<<<< INSERT SCRIPT HERE
EOF

exit 0