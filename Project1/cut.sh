export PS4="% "
cut -f1 -d, /usr/share/distro-info/ubuntu.csv
cut -f2 -d, /usr/share/distro-info/ubuntu.csv
cut -f2-3 -d, /usr/share/distro-info/ubuntu.csv
cut -f1-3 -d, /usr/share/distro-info/ubuntu.csv
cut -f4- -d, /usr/share/distro-info/ubuntu.csv
cut -f4- -d, --output-delimiter=\| /usr/share/distro-info/ubuntu.csv
