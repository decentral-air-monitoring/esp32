# How to set up the Server
 * useradd particle
 * mkdir /var/log/particle
 * chown particle:particle /var/log/particle
 * cd /opt
 * git clone https://github.com/firefly-serenity/decentral-air-quality-monitoring.git
 * cd /opt/decentral-air-quality-monitoring/server/particle
 * virtualenv -p python3 venv
 * source venv/bin/activate
 * pip3 install -r requirements.txt
 * python3 mqtt-client.py
 
 
