// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#include "GQLObjects.h"

#include "graphqlservice/introspection/Introspection.h"

#include <algorithm>
#include <functional>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include <iostream>

using namespace std::literals;

namespace graphql::database {
namespace object {

Query::Query()
	: service::Object({
		"Query"
	}, {
		{ R"gql(__type)gql"sv, [this](service::ResolverParams&& params) { return resolve_type(std::move(params)); } },
		{ R"gql(author)gql"sv, [this](service::ResolverParams&& params) { return resolveAuthor(std::move(params)); } },
		{ R"gql(search)gql"sv, [this](service::ResolverParams&& params) { return resolveSearch(std::move(params)); } },
		{ R"gql(__schema)gql"sv, [this](service::ResolverParams&& params) { return resolve_schema(std::move(params)); } },
		{ R"gql(__typename)gql"sv, [this](service::ResolverParams&& params) { return resolve_typename(std::move(params)); } },
		{ R"gql(allAuthors)gql"sv, [this](service::ResolverParams&& params) { return resolveAllAuthors(std::move(params)); } }
	})
	, _schema(GetSchema())
{
}

service::FieldResult<std::shared_ptr<Author>> Query::getAuthor([[maybe_unused]] service::FieldParams&& params, std::optional<response::IntType>&& id) const
{
	std::shared_ptr<Author> result;
	if(id){
		std::cout << id.value() << std::endl;
		result = Author::get(id.value());
	}
	return result;
}

std::future<service::ResolverResult> Query::resolveAuthor(service::ResolverParams&& params)
{
	auto argId = service::ModifiedArgument<response::IntType>::require<service::TypeModifier::Nullable>("id", params.arguments);
	std::unique_lock resolverLock(_resolverMutex);
	auto directives = std::move(params.fieldDirectives);
	auto result = getAuthor(service::FieldParams(std::move(params), std::move(directives)), std::move(argId));
	resolverLock.unlock();

	return service::ModifiedResult<Author>::convert<service::TypeModifier::Nullable>(std::move(result), std::move(params));
}

service::FieldResult<std::optional<std::vector<std::shared_ptr<Author>>>> Query::getAllAuthors(service::FieldParams&&) const
{
	std::vector<std::shared_ptr<Author>> result = Author::read_all();
	return result;
}

std::future<service::ResolverResult> Query::resolveAllAuthors(service::ResolverParams&& params)
{
	std::unique_lock resolverLock(_resolverMutex);
	auto directives = std::move(params.fieldDirectives);
	auto result = getAllAuthors(service::FieldParams(std::move(params), std::move(directives)));
	resolverLock.unlock();

	return service::ModifiedResult<Author>::convert<service::TypeModifier::Nullable, service::TypeModifier::List, service::TypeModifier::Nullable>(std::move(result), std::move(params));
}

service::FieldResult<std::vector<std::shared_ptr<Author>>> Query::getSearch([[maybe_unused]] service::FieldParams&& param, response::StringType&& termArg1, response::StringType&& termArg2) const
{
	std::cout << termArg1 << "," << termArg2 << std::endl;
	std::vector<std::shared_ptr<Author>> result = Author::search(termArg1,termArg2);
	return result;
}

std::future<service::ResolverResult> Query::resolveSearch(service::ResolverParams&& params)
{
	auto argTerm1 = service::ModifiedArgument<response::StringType>::require("term1", params.arguments);
	auto argTerm2 = service::ModifiedArgument<response::StringType>::require("term2", params.arguments);
	std::unique_lock resolverLock(_resolverMutex);
	auto directives = std::move(params.fieldDirectives);
	auto result = getSearch(service::FieldParams(std::move(params), std::move(directives)), std::move(argTerm1), std::move(argTerm2));
	resolverLock.unlock();

	return service::ModifiedResult<Author>::convert<service::TypeModifier::List>(std::move(result), std::move(params));
}

std::future<service::ResolverResult> Query::resolve_typename(service::ResolverParams&& params)
{
	return service::ModifiedResult<response::StringType>::convert(response::StringType{ R"gql(Query)gql" }, std::move(params));
}

std::future<service::ResolverResult> Query::resolve_schema(service::ResolverParams&& params)
{
	return service::ModifiedResult<service::Object>::convert(std::static_pointer_cast<service::Object>(std::make_shared<introspection::Schema>(_schema)), std::move(params));
}

std::future<service::ResolverResult> Query::resolve_type(service::ResolverParams&& params)
{
	auto argName = service::ModifiedArgument<response::StringType>::require("name", params.arguments);
	const auto& baseType = _schema->LookupType(argName);
	std::shared_ptr<introspection::object::Type> result { baseType ? std::make_shared<introspection::Type>(baseType) : nullptr };

	return service::ModifiedResult<introspection::object::Type>::convert<service::TypeModifier::Nullable>(result, std::move(params));
}

} // namespace object

void AddQueryDetails(std::shared_ptr<schema::ObjectType> typeQuery, const std::shared_ptr<schema::Schema>& schema)
{
	typeQuery->AddFields({
		schema::Field::Make(R"gql(author)gql"sv, R"md()md"sv, std::nullopt, schema->LookupType("Author"), {
			schema::InputValue::Make(R"gql(id)gql"sv, R"md()md"sv, schema->LookupType("Int"), R"gql()gql"sv)
		}),
		schema::Field::Make(R"gql(allAuthors)gql"sv, R"md()md"sv, std::nullopt, schema->WrapType(introspection::TypeKind::LIST, schema->LookupType("Author"))),
		schema::Field::Make(R"gql(search)gql"sv, R"md()md"sv, std::nullopt, schema->WrapType(introspection::TypeKind::NON_NULL, schema->WrapType(introspection::TypeKind::LIST, schema->WrapType(introspection::TypeKind::NON_NULL, schema->LookupType("Author")))), {
			schema::InputValue::Make(R"gql(term1)gql"sv, R"md()md"sv, schema->WrapType(introspection::TypeKind::NON_NULL, schema->LookupType("String")), R"gql()gql"sv),
			schema::InputValue::Make(R"gql(term2)gql"sv, R"md()md"sv, schema->WrapType(introspection::TypeKind::NON_NULL, schema->LookupType("String")), R"gql()gql"sv)
		})
	});
}

} // namespace graphql::database
