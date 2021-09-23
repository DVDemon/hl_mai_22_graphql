// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#pragma once

#ifndef QUERYOBJECT_H
#define QUERYOBJECT_H

#include "GQLSchema.h"

namespace graphql::database::object {

class Query
	: public service::Object
{
protected:
	

public:
	Query();
	virtual service::FieldResult<std::shared_ptr<Author>> getAuthor(service::FieldParams&& params, std::optional<response::IntType>&& idArg) const;
	virtual service::FieldResult<std::optional<std::vector<std::shared_ptr<Author>>>> getAllAuthors(service::FieldParams&& params) const;
	virtual service::FieldResult<std::vector<std::shared_ptr<Author>>> getSearch(service::FieldParams&& params, response::StringType&& termArg1, response::StringType&& termArg2) const;

private:
	std::future<service::ResolverResult> resolveAuthor(service::ResolverParams&& params);
	std::future<service::ResolverResult> resolveAllAuthors(service::ResolverParams&& params);
	std::future<service::ResolverResult> resolveSearch(service::ResolverParams&& params);

	std::future<service::ResolverResult> resolve_typename(service::ResolverParams&& params);
	std::future<service::ResolverResult> resolve_schema(service::ResolverParams&& params);
	std::future<service::ResolverResult> resolve_type(service::ResolverParams&& params);

	std::shared_ptr<schema::Schema> _schema;
};

} // namespace graphql::database::object

#endif // QUERYOBJECT_H
