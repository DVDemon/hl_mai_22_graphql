# Пример по курсу Архитектуре программных систем
### GCC 11
sudo apt install build-essential manpages-dev software-properties-common
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt update && sudo apt install gcc-11 g++-11

### Зависимости
https://github.com/Tencent/rapidjson.git
https://github.com/taocpp/PEGTL.git
git clone --recurse-submodules https://github.com/microsoft/cppgraphqlgen.git

### Генерация схемы
/usr/local/bin/cppgraphqlgen/schemagen  -s database/schema.graphql -p GQL -n database


### implement stubs
ServiceMock.h
ServiceMock.cpp

### Полезные ссылки про GraphQL

https://graphql.org/graphql-js/language/
https://spec.graphql.org/October2021/
https://www.howtographql.com/basics/0-introduction/

### Схема

schema {
  query: Query
}

type Query {
  author(id: Int): Author
  allAuthors: [Author]
  search(term1: String!,term2: String!): [Author!]!
}

type Author  {
  id: Int
  first_name:String!
  last_name:String!
  email:String!
  title:String!
}

query {
    search(term1:"A", term2:"B"){
        id,
        first_name,
        last_name,
        email,
        title
    }
}

### Примеры запросов

query {
    search(term1:"I%", term2:"I%"){
        id,
        first_name,
        last_name,
        email,
        title
    }
}

query {
    allAuthors{
        id,
        first_name,
        last_name,
        email,
        title
    }
}

query {
    author(id:10){
        id,
        first_name,
        last_name,
        email,
        title
    }
}
