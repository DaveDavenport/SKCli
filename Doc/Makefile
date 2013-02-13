TXT_SOURCES=$(wildcard *.txt)
HTML_SOURCES=$(TXT_SOURCES:%.txt=%.html)

all: $(HTML_SOURCES)

%.html: %.txt
	asciidoc $^

clean:
	rm -rf $(HTML_SOURCES)
