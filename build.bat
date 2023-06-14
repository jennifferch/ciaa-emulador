for /D %%s in (examples/*) do @echo Building examples/%%s... && node cli.js -i examples/%%s -o outUser/ --compiler-opts "-Os"
