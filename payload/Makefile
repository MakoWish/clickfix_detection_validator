.PHONY: all clean

all:
	dotnet publish Syncovery.csproj \
		-c Release \
		-r win-x64 \
		--self-contained true \
		-p:PublishSingleFile=true \
		-o out

clean:
	rm -rf bin obj out
