# Пример по курсу Архитектуре программных систем

https://graphql.org/graphql-js/language/

https://github.com/Tencent/rapidjson.git

https://github.com/taocpp/PEGTL.git

**git clone --recurse-submodules** https://github.com/microsoft/cppgraphqlgen.git

/usr/local/bin/cppgraphqlgen/schemagen  -s database/schema.graphql -p GQL -n database

https://spec.graphql.org/October2021/

https://www.howtographql.com/basics/0-introduction/

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
    search(term1:"I"", term2:"I"){
        id,
        first_name,
        last_name,
        email,
        title
    }



query {
    allAuthors{
        id,
        first_name,
        last_name,
        email,
        title
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
