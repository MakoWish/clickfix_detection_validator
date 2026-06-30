.PHONY: all clean

all:
	x86_64-w64-mingw32-gcc nexus_connector_sim.c -Os -s -o NexusConnector.exe
	python3 -m zipfile -c nexus_payload.zip NexusConnector.exe

clean:
	rm -f NexusConnector.exe nexus_payload.zip
