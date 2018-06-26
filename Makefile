slides:
	@pandoc rust-ffi.md \
	--to revealjs \
	--output rust-ffi.html \
	-V revealjs-url=http://revealjs.com \
	-V theme=moon \
	-V progress=true \
	-V slideNumber=true \
	-V history=true \
	--standalone --slide-level 2

pdf: slides
	@echo "This might take a while, I'll beep when it's done"
	@echo ""
	npx decktape reveal `pwd`/rust-ffi.html  rust-ffi.pdf
	@echo -e "\a"
