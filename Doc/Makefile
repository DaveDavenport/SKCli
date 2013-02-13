BUILD_DIR_HTML=$(BUILD_DIR)html/
TXT_SOURCES=$(wildcard *.txt)
HTML_SOURCES=$(TXT_SOURCES:%.txt=$(BUILD_DIR_HTML)%.html)

all: $(HTML_SOURCES)

$(BUILD_DIR_HTML):
	@mkdir -p "$@"

$(BUILD_DIR_HTML)%.html: %.txt $(BUILD_DIR_HTML)
	asciidoc -o $@ $<

clean:
	@rm -rf $(HTML_SOURCES)
