#include "ServiceMock.h"
#include <iostream>
#include "database.h"
#include <Poco/Data/MySQL/Connector.h>
#include <Poco/Data/MySQL/MySQLException.h>
#include <Poco/Data/SessionFactory.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

using namespace Poco::Data::Keywords;

namespace graphql::database::object
{

    std::shared_ptr<graphql::service::Request> GetService()
    {
        std::shared_ptr<Query> query = std::make_shared<Query>(std::make_shared<QueryImpl>());
        auto service = std::make_shared<Operations>(std::move(query));
        return service;
    }

    void QueryImpl::beginSelectionSet([[maybe_unused]] const service::SelectionSetParams &params) const
    {
    }
    void QueryImpl::endSelectionSet([[maybe_unused]] const service::SelectionSetParams &params) const
    {
    }

    std::shared_ptr<Author> QueryImpl::getAuthor([[maybe_unused]] std::optional<int> &&idArg) const
    {
        auto author_impl = std::make_shared<AuthorImpl>();
        try
        {
            Poco::Data::Session session = ::db::Database::get().create_session_read();
            Poco::Data::Statement select(session);
            select << "SELECT id, first_name, last_name, email, title FROM Author where id=?",
                into(author_impl->_id),
                into(author_impl->_first_name),
                into(author_impl->_last_name),
                into(author_impl->_email),
                into(author_impl->_title),
                use(idArg.value()),
                range(0, 1); //  iterate over result set one row at a time

            if (!select.done())
            {
                if (!select.execute())
                    throw std::logic_error("Record not found");
            }
            return std::make_shared<Author>(author_impl);
        }

        catch (Poco::Data::MySQL::ConnectionException &e)
        {
            throw std::logic_error(e.what());
        }
        catch (Poco::Data::MySQL::StatementException &e)
        {
            throw std::logic_error(e.what());
        }
    }

    std::vector<std::shared_ptr<Author>> QueryImpl::getAllAuthors() const
    {
        try
        {
            Poco::Data::Session session = ::db::Database::get().create_session_read();
            Poco::Data::Statement select(session);

            std::vector<std::shared_ptr<Author>> result;
            auto author_impl = std::make_shared<AuthorImpl>();
            select << "SELECT id, first_name, last_name, email, title FROM Author",
                into(author_impl->_id),
                into(author_impl->_first_name),
                into(author_impl->_last_name),
                into(author_impl->_email),
                into(author_impl->_title),
                range(0, 1); //  iterate over result set one row at a time

            while (!select.done())
            {
                if (select.execute())
                {
                    auto a = std::make_shared<AuthorImpl>();
                    *a = *author_impl;
                    result.push_back(std::make_shared<Author>(a));
                }
            }
            return result;
        }
        catch (Poco::Data::MySQL::ConnectionException &e)
        {
            throw std::logic_error(e.what());
        }
        catch (Poco::Data::MySQL::StatementException &e)
        {
            throw std::logic_error(e.what());
        }
    }

    std::vector<std::shared_ptr<Author>> QueryImpl::getSearch([[maybe_unused]] std::string &&term1Arg, [[maybe_unused]] std::string &&term2Arg) const
    {
        try
        {
            Poco::Data::Session session = ::db::Database::get().create_session_read();
            Poco::Data::Statement select(session);

            std::vector<std::shared_ptr<Author>> result;
            auto author_impl = std::make_shared<AuthorImpl>();
            select << "SELECT id, first_name, last_name, email, title FROM Author WHERE first_name LIKE ? AND last_name LIKE ?",
                into(author_impl->_id),
                into(author_impl->_first_name),
                into(author_impl->_last_name),
                into(author_impl->_email),
                into(author_impl->_title),
                use(term1Arg),
                use(term2Arg),
                range(0, 1); //  iterate over result set one row at a time

            while (!select.done())
            {
                if (select.execute())
                {
                    auto a = std::make_shared<AuthorImpl>();
                    *a = *author_impl;
                    result.push_back(std::make_shared<Author>(a));
                }
            }
            return result;
        }
        catch (Poco::Data::MySQL::ConnectionException &e)
        {
            throw std::logic_error(e.what());
        }
        catch (Poco::Data::MySQL::StatementException &e)
        {
            throw std::logic_error(e.what());
        }
    }

}