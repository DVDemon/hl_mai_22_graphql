// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#pragma once

#ifndef AUTHOROBJECT_H
#define AUTHOROBJECT_H

#include "GQLSchema.h"
#include <vector>

namespace graphql::database::object
{

	class Author
		: public service::Object
	{
	protected:
		
		long _id;
		std::string _first_name;
		std::string _last_name;
		std::string _email;
		std::string _title;

	public:
		Author();
		Author(long id);

		virtual service::FieldResult<std::optional<response::IntType>> getId(service::FieldParams &&params) const;
		virtual service::FieldResult<response::StringType> getFirst_name(service::FieldParams &&params) const;
		virtual service::FieldResult<response::StringType> getLast_name(service::FieldParams &&params) const;
		virtual service::FieldResult<response::StringType> getEmail(service::FieldParams &&params) const;
		virtual service::FieldResult<response::StringType> getTitle(service::FieldParams &&params) const;

		static std::vector<std::shared_ptr<Author>> read_all();

	private:
		std::future<service::ResolverResult> resolveId(service::ResolverParams &&params);
		std::future<service::ResolverResult> resolveFirst_name(service::ResolverParams &&params);
		std::future<service::ResolverResult> resolveLast_name(service::ResolverParams &&params);
		std::future<service::ResolverResult> resolveEmail(service::ResolverParams &&params);
		std::future<service::ResolverResult> resolveTitle(service::ResolverParams &&params);

		std::future<service::ResolverResult> resolve_typename(service::ResolverParams &&params);
	};

} // namespace graphql::database::object

#endif // AUTHOROBJECT_H
