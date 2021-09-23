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
#include "database.h"

#include "../config/config.h"
#include <Poco/Data/MySQL/Connector.h>
#include <Poco/Data/MySQL/MySQLException.h>
#include <Poco/Data/SessionFactory.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

using namespace Poco::Data::Keywords;
using Poco::Data::Session;
using Poco::Data::Statement;

using namespace std::literals;

namespace graphql::database
{
	namespace object
	{

		Author::Author()
			: service::Object({"Author"}, {{R"gql(id)gql"sv, [this](service::ResolverParams &&params)
											{ return resolveId(std::move(params)); }},
										   {R"gql(email)gql"sv, [this](service::ResolverParams &&params)
											{ return resolveEmail(std::move(params)); }},
										   {R"gql(title)gql"sv, [this](service::ResolverParams &&params)
											{ return resolveTitle(std::move(params)); }},
										   {R"gql(last_name)gql"sv, [this](service::ResolverParams &&params)
											{ return resolveLast_name(std::move(params)); }},
										   {R"gql(__typename)gql"sv, [this](service::ResolverParams &&params)
											{ return resolve_typename(std::move(params)); }},
										   {R"gql(first_name)gql"sv, [this](service::ResolverParams &&params)
											{ return resolveFirst_name(std::move(params)); }}})
		{
			_id = 0;
		}

		std::shared_ptr<Author> Author::get(long id)
		{
			std::shared_ptr<Author> result;
			try
			{
				Poco::Data::Session session = ::db::Database::get().create_session_read();
				Poco::Data::Statement select(session);
				result = std::make_shared<Author>();
				select << "SELECT id, first_name, last_name, email, title FROM Author where id=?",
					into(result->_id),
					into(result->_first_name),
					into(result->_last_name),
					into(result->_email),
					into(result->_title),
					use(id),
					range(0, 1); //  iterate over result set one row at a time

				if (!select.done())
				{
					select.execute();
				}
				return result;
			}

			catch (Poco::Data::MySQL::ConnectionException &e)
			{
				std::cout << "connection:" << e.what() << std::endl;
				//throw;
			}
			catch (Poco::Data::MySQL::StatementException &e)
			{

				std::cout << "statement:" << e.what() << std::endl;
				//throw;
			}

			return std::shared_ptr<Author>();
		}

		std::vector<std::shared_ptr<Author>> Author::search(std::string first_name, std::string last_name){
			try
        {
            Poco::Data::Session session = ::db::Database::get().create_session_read();
            Statement select(session);
            std::vector<std::shared_ptr<Author>> result;
            std::shared_ptr<Author> a = std::make_shared<Author>();
            select << "SELECT id, first_name, last_name, email, title FROM Author where first_name LIKE ? and last_name LIKE ?",
                into(a->_id),
                into(a->_first_name),
                into(a->_last_name),
                into(a->_email),
                into(a->_title),
                use(first_name),
                use(last_name),
                range(0, 1); //  iterate over result set one row at a time

            while (!select.done())
            {
                select.execute();
                result.push_back(a);
            }
            return result;
        }

        catch (Poco::Data::MySQL::ConnectionException &e)
        {
            std::cout << "connection:" << e.what() << std::endl;
            throw;
        }
        catch (Poco::Data::MySQL::StatementException &e)
        {

            std::cout << "statement:" << e.what() << std::endl;
            throw;
        }
		}
		std::vector<std::shared_ptr<Author>> Author::read_all()
		{
			try
			{
				Poco::Data::Session session = ::db::Database::get().create_session_read();
				Statement select(session);
				std::vector<std::shared_ptr<Author>> result;
				std::shared_ptr<Author> a = std::make_shared<Author>();
				select << "SELECT id, first_name, last_name, email, title FROM Author",
					into(a->_id),
					into(a->_first_name),
					into(a->_last_name),
					into(a->_email),
					into(a->_title),
					range(0, 1); //  iterate over result set one row at a time

				while (!select.done())
				{
					select.execute();
					result.push_back(a);
				}
				return result;
			}

			catch (Poco::Data::MySQL::ConnectionException &e)
			{
				std::cout << "connection:" << e.what() << std::endl;
				throw;
			}
			catch (Poco::Data::MySQL::StatementException &e)
			{

				std::cout << "statement:" << e.what() << std::endl;
				throw;
			}
		}

		service::FieldResult<std::optional<response::IntType>> Author::getId(service::FieldParams &&) const
		{
			return _id;
		}

		std::future<service::ResolverResult> Author::resolveId(service::ResolverParams &&params)
		{
			std::unique_lock resolverLock(_resolverMutex);
			auto directives = std::move(params.fieldDirectives);
			auto result = getId(service::FieldParams(std::move(params), std::move(directives)));
			resolverLock.unlock();

			return service::ModifiedResult<response::IntType>::convert<service::TypeModifier::Nullable>(std::move(result), std::move(params));
		}

		service::FieldResult<response::StringType> Author::getFirst_name(service::FieldParams &&) const
		{
			return _first_name;
		}

		std::future<service::ResolverResult> Author::resolveFirst_name(service::ResolverParams &&params)
		{
			std::unique_lock resolverLock(_resolverMutex);
			auto directives = std::move(params.fieldDirectives);
			auto result = getFirst_name(service::FieldParams(std::move(params), std::move(directives)));
			resolverLock.unlock();

			return service::ModifiedResult<response::StringType>::convert(std::move(result), std::move(params));
		}

		service::FieldResult<response::StringType> Author::getLast_name(service::FieldParams &&) const
		{
			return _last_name;
		}

		std::future<service::ResolverResult> Author::resolveLast_name(service::ResolverParams &&params)
		{
			std::unique_lock resolverLock(_resolverMutex);
			auto directives = std::move(params.fieldDirectives);
			auto result = getLast_name(service::FieldParams(std::move(params), std::move(directives)));
			resolverLock.unlock();

			return service::ModifiedResult<response::StringType>::convert(std::move(result), std::move(params));
		}

		service::FieldResult<response::StringType> Author::getEmail(service::FieldParams &&) const
		{
			return _email;
		}

		std::future<service::ResolverResult> Author::resolveEmail(service::ResolverParams &&params)
		{
			std::unique_lock resolverLock(_resolverMutex);
			auto directives = std::move(params.fieldDirectives);
			auto result = getEmail(service::FieldParams(std::move(params), std::move(directives)));
			resolverLock.unlock();

			return service::ModifiedResult<response::StringType>::convert(std::move(result), std::move(params));
		}

		service::FieldResult<response::StringType> Author::getTitle(service::FieldParams &&) const
		{
			return _title;
		}

		std::future<service::ResolverResult> Author::resolveTitle(service::ResolverParams &&params)
		{
			std::unique_lock resolverLock(_resolverMutex);
			auto directives = std::move(params.fieldDirectives);
			auto result = getTitle(service::FieldParams(std::move(params), std::move(directives)));
			resolverLock.unlock();

			return service::ModifiedResult<response::StringType>::convert(std::move(result), std::move(params));
		}

		std::future<service::ResolverResult> Author::resolve_typename(service::ResolverParams &&params)
		{
			return service::ModifiedResult<response::StringType>::convert(response::StringType{R"gql(Author)gql"}, std::move(params));
		}

	} // namespace object

	void AddAuthorDetails(std::shared_ptr<schema::ObjectType> typeAuthor, const std::shared_ptr<schema::Schema> &schema)
	{
		typeAuthor->AddFields({schema::Field::Make(R"gql(id)gql"sv, R"md()md"sv, std::nullopt, schema->LookupType("Int")),
							   schema::Field::Make(R"gql(first_name)gql"sv, R"md()md"sv, std::nullopt, schema->WrapType(introspection::TypeKind::NON_NULL, schema->LookupType("String"))),
							   schema::Field::Make(R"gql(last_name)gql"sv, R"md()md"sv, std::nullopt, schema->WrapType(introspection::TypeKind::NON_NULL, schema->LookupType("String"))),
							   schema::Field::Make(R"gql(email)gql"sv, R"md()md"sv, std::nullopt, schema->WrapType(introspection::TypeKind::NON_NULL, schema->LookupType("String"))),
							   schema::Field::Make(R"gql(title)gql"sv, R"md()md"sv, std::nullopt, schema->WrapType(introspection::TypeKind::NON_NULL, schema->LookupType("String")))});
	}

} // namespace graphql::database
