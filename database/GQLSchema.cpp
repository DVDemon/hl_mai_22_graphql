// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#include "GQLObjects.h"

#include "graphqlservice/introspection/Introspection.h"

#include <algorithm>
#include <array>
#include <functional>
#include <sstream>
#include <stdexcept>
#include <string_view>
#include <tuple>
#include <vector>

using namespace std::literals;

namespace graphql {
namespace database {

Operations::Operations(std::shared_ptr<object::Query> query)
	: service::Request({
		{ "query", query }
	}, GetSchema())
	, _query(std::move(query))
{
}

void AddTypesToSchema(const std::shared_ptr<schema::Schema>& schema)
{
	auto typeQuery = schema::ObjectType::Make(R"gql(Query)gql"sv, R"md()md");
	schema->AddType(R"gql(Query)gql"sv, typeQuery);
	auto typeAuthor = schema::ObjectType::Make(R"gql(Author)gql"sv, R"md()md");
	schema->AddType(R"gql(Author)gql"sv, typeAuthor);

	AddQueryDetails(typeQuery, schema);
	AddAuthorDetails(typeAuthor, schema);

	schema->AddQueryType(typeQuery);
}

std::shared_ptr<schema::Schema> GetSchema()
{
	static std::weak_ptr<schema::Schema> s_wpSchema;
	auto schema = s_wpSchema.lock();

	if (!schema)
	{
		schema = std::make_shared<schema::Schema>(false);
		introspection::AddTypesToSchema(schema);
		AddTypesToSchema(schema);
		s_wpSchema = schema;
	}

	return schema;
}

} // namespace database
} // namespace graphql
