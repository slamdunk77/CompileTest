FROM gcc:10
WORKDIR /app/
COPY ./* ./
RUN gcc LexicalAnalysis.c -o LexicalAnalysis
RUN chmod +x LexicalAnalysis
