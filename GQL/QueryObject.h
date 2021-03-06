// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#pragma once

#ifndef QUERYOBJECT_H
#define QUERYOBJECT_H

#include "GQLSchema.h"

namespace graphql::database::object {
namespace methods::QueryHas {

template <class TImpl>
concept getAuthorWithParams = requires (TImpl impl, service::FieldParams params, std::optional<int> idArg)
{
	{ service::AwaitableObject<std::shared_ptr<Author>> { impl.getAuthor(std::move(params), std::move(idArg)) } };
};

template <class TImpl>
concept getAuthor = requires (TImpl impl, std::optional<int> idArg)
{
	{ service::AwaitableObject<std::shared_ptr<Author>> { impl.getAuthor(std::move(idArg)) } };
};

template <class TImpl>
concept getAllAuthorsWithParams = requires (TImpl impl, service::FieldParams params)
{
	{ service::AwaitableObject<std::optional<std::vector<std::shared_ptr<Author>>>> { impl.getAllAuthors(std::move(params)) } };
};

template <class TImpl>
concept getAllAuthors = requires (TImpl impl)
{
	{ service::AwaitableObject<std::optional<std::vector<std::shared_ptr<Author>>>> { impl.getAllAuthors() } };
};

template <class TImpl>
concept getSearchWithParams = requires (TImpl impl, service::FieldParams params, std::string term1Arg, std::string term2Arg)
{
	{ service::AwaitableObject<std::vector<std::shared_ptr<Author>>> { impl.getSearch(std::move(params), std::move(term1Arg), std::move(term2Arg)) } };
};

template <class TImpl>
concept getSearch = requires (TImpl impl, std::string term1Arg, std::string term2Arg)
{
	{ service::AwaitableObject<std::vector<std::shared_ptr<Author>>> { impl.getSearch(std::move(term1Arg), std::move(term2Arg)) } };
};

template <class TImpl>
concept beginSelectionSet = requires (TImpl impl, const service::SelectionSetParams params)
{
	{ impl.beginSelectionSet(params) };
};

template <class TImpl>
concept endSelectionSet = requires (TImpl impl, const service::SelectionSetParams params)
{
	{ impl.endSelectionSet(params) };
};

} // namespace methods::QueryHas

class Query final
	: public service::Object
{
private:
	service::AwaitableResolver resolveAuthor(service::ResolverParams&& params) const;
	service::AwaitableResolver resolveAllAuthors(service::ResolverParams&& params) const;
	service::AwaitableResolver resolveSearch(service::ResolverParams&& params) const;

	service::AwaitableResolver resolve_typename(service::ResolverParams&& params) const;

	struct Concept
	{
		virtual ~Concept() = default;

		virtual void beginSelectionSet(const service::SelectionSetParams& params) const = 0;
		virtual void endSelectionSet(const service::SelectionSetParams& params) const = 0;

		virtual service::AwaitableObject<std::shared_ptr<Author>> getAuthor(service::FieldParams&& params, std::optional<int>&& idArg) const = 0;
		virtual service::AwaitableObject<std::optional<std::vector<std::shared_ptr<Author>>>> getAllAuthors(service::FieldParams&& params) const = 0;
		virtual service::AwaitableObject<std::vector<std::shared_ptr<Author>>> getSearch(service::FieldParams&& params, std::string&& term1Arg, std::string&& term2Arg) const = 0;
	};

	template <class T>
	struct Model
		: Concept
	{
		Model(std::shared_ptr<T>&& pimpl) noexcept
			: _pimpl { std::move(pimpl) }
		{
		}

		service::AwaitableObject<std::shared_ptr<Author>> getAuthor(service::FieldParams&& params, std::optional<int>&& idArg) const final
		{
			if constexpr (methods::QueryHas::getAuthorWithParams<T>)
			{
				return { _pimpl->getAuthor(std::move(params), std::move(idArg)) };
			}
			else
			{
				static_assert(methods::QueryHas::getAuthor<T>, R"msg(Query::getAuthor is not implemented)msg");
				return { _pimpl->getAuthor(std::move(idArg)) };
			}
		}

		service::AwaitableObject<std::optional<std::vector<std::shared_ptr<Author>>>> getAllAuthors(service::FieldParams&& params) const final
		{
			if constexpr (methods::QueryHas::getAllAuthorsWithParams<T>)
			{
				return { _pimpl->getAllAuthors(std::move(params)) };
			}
			else
			{
				static_assert(methods::QueryHas::getAllAuthors<T>, R"msg(Query::getAllAuthors is not implemented)msg");
				return { _pimpl->getAllAuthors() };
			}
		}

		service::AwaitableObject<std::vector<std::shared_ptr<Author>>> getSearch(service::FieldParams&& params, std::string&& term1Arg, std::string&& term2Arg) const final
		{
			if constexpr (methods::QueryHas::getSearchWithParams<T>)
			{
				return { _pimpl->getSearch(std::move(params), std::move(term1Arg), std::move(term2Arg)) };
			}
			else
			{
				static_assert(methods::QueryHas::getSearch<T>, R"msg(Query::getSearch is not implemented)msg");
				return { _pimpl->getSearch(std::move(term1Arg), std::move(term2Arg)) };
			}
		}

		void beginSelectionSet(const service::SelectionSetParams& params) const final
		{
			if constexpr (methods::QueryHas::beginSelectionSet<T>)
			{
				_pimpl->beginSelectionSet(params);
			}
		}

		void endSelectionSet(const service::SelectionSetParams& params) const final
		{
			if constexpr (methods::QueryHas::endSelectionSet<T>)
			{
				_pimpl->endSelectionSet(params);
			}
		}

	private:
		const std::shared_ptr<T> _pimpl;
	};

	Query(std::unique_ptr<const Concept>&& pimpl) noexcept;

	service::TypeNames getTypeNames() const noexcept;
	service::ResolverMap getResolvers() const noexcept;

	void beginSelectionSet(const service::SelectionSetParams& params) const final;
	void endSelectionSet(const service::SelectionSetParams& params) const final;

	const std::unique_ptr<const Concept> _pimpl;

public:
	template <class T>
	Query(std::shared_ptr<T> pimpl) noexcept
		: Query { std::unique_ptr<const Concept> { std::make_unique<Model<T>>(std::move(pimpl)) } }
	{
	}
};

} // namespace graphql::database::object

#endif // QUERYOBJECT_H
