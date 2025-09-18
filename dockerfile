FROM ubuntu:20.04

# Установка зависимостей
RUN apt-get update && apt-get install -y \
    cmake \
    g++ \
    make \
    && rm -rf /var/lib/apt/lists/*

# Копирование исходников (ИСКЛЮЧАЯ build папку и кэш)
COPY . /app
WORKDIR /app

# УДАЛИТЬ старый CMakeCache.txt если он есть и сделать чистую сборку
RUN rm -f CMakeCache.txt && \
    rm -rf build && \
    mkdir -p build && \
    cd build && \
    cmake -DCMAKE_BUILD_TYPE=Release .. && \
    cmake --build . --target rpn_calculator --parallel $(nproc)

CMD ["./build/rpn_calculator"]
