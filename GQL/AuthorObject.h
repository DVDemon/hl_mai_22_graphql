// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#pragma once

#ifndef AUTHOROBJECT_H
#define AUTHOROBJECT_H

#include "GQLSchema.h"

namespace graphql::database::object {
namespace methods::AuthorHas {

template <class TImpl>
concept getIdWithParams = requires (TImpl impl, service::FieldParams params)
{
	{ service::AwaitableScalar<std::optional<int>> { impl.getId(std::move(params)) } };
};

template <class TImpl>
concept getId = requires (TImpl impl)
{
	{ service::AwaitableScalar<std::optional<int>> { impl.getId() } };
};

template <class TImpl>
concept getFirst_nameWithParams = requires (TImpl impl, service::FieldParams params)
{
	{ service::AwaitableScalar<std::string> { impl.getFirst_name(std::move(params)) } };
};

template <class TImpl>
concept getFirst_name = requires (TImpl impl)
{
	{ service::AwaitableScalar<std::string> { impl.getFirst_name() } };
};

template <class TImpl>
concept getLast_nameWithParams = requires (TImpl impl, service::FieldParams params)
{
	{ service::AwaitableScalar<std::string> { impl.getLast_name(std::move(params)) } };
};

template <class TImpl>
concept getLast_name = requires (TImpl impl)
{
	{ service::AwaitableScalar<std::string> { impl.getLast_name() } };
};

template <class TImpl>
concept getEmailWithParams = requires (TImpl impl, service::FieldParams params)
{
	{ service::AwaitableScalar<std::string> { impl.getEmail(std::move(params)) } };
};

template <class TImpl>
concept getEmail = requires (TImpl impl)
{
	{ service::AwaitableScalar<std::string> { impl.getEmail() } };
};

template <class TImpl>
concept getTitleWithParams = requires (TImpl impl, service::FieldParams params)
{
	{ service::AwaitableScalar<std::string> { impl.getTitle(std::move(params)) } };
};

template <class TImpl>
concept getTitle = requires (TImpl impl)
{
	{ service::AwaitableScalar<std::string> { impl.getTitle() } };
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

} // namespace methods::AuthorHas

class Author final
	: public service::Object
{
private:
	service::AwaitableResolver resolveId(service::ResolverParams&& params) const;
	service::AwaitableResolver resolveFirst_name(service::ResolverParams&& params) const;
	service::AwaitableResolver resolveLast_name(service::ResolverParams&& params) const;
	service::AwaitableResolver resolveEmail(service::ResolverParams&& params) const;
	service::AwaitableResolver resolveTitle(service::ResolverParams&& params) const;

	service::AwaitableResolver resolve_typename(service::ResolverParams&& params) const;

	struct Concept
	{
		virtual ~Concept() = default;

		virtual void beginSelectionSet(const service::SelectionSetParams& params) const = 0;
		virtual void endSelectionSet(const service::SelectionSetParams& params) const = 0;

		virtual service::AwaitableScalar<std::optional<int>> getId(service::FieldParams&& params) const = 0;
		virtual service::AwaitableScalar<std::string> getFirst_name(service::FieldParams&& params) const = 0;
		virtual service::AwaitableScalar<std::string> getLast_name(service::FieldParams&& params) const = 0;
		virtual service::AwaitableScalar<std::string> getEmail(service::FieldParams&& params) const = 0;
		virtual service::AwaitableScalar<std::string> getTitle(service::FieldParams&& params) const = 0;
	};

	template <class T>
	struct Model
		: Concept
	{
		Model(std::shared_ptr<T>&& pimpl) noexcept
			: _pimpl { std::move(pimpl) }
		{
		}

		service::AwaitableScalar<std::optional<int>> getId(service::FieldParams&& params) const final
		{
			if constexpr (methods::AuthorHas::getIdWithParams<T>)
			{
				return { _pimpl->getId(std::move(params)) };
			}
			else
			{
				static_assert(methods::AuthorHas::getId<T>, R"msg(Author::getId is not implemented)msg");
				return { _pimpl->getId() };
			}
		}

		service::AwaitableScalar<std::string> getFirst_name(service::FieldParams&& params) const final
		{
			if constexpr (methods::AuthorHas::getFirst_nameWithParams<T>)
			{
				return { _pimpl->getFirst_name(std::move(params)) };
			}
			else
			{
				static_assert(methods::AuthorHas::getFirst_name<T>, R"msg(Author::getFirst_name is not implemented)msg");
				return { _pimpl->getFirst_name() };
			}
		}

		service::AwaitableScalar<std::string> getLast_name(service::FieldParams&& params) const final
		{
			if constexpr (methods::AuthorHas::getLast_nameWithParams<T>)
			{
				return { _pimpl->getLast_name(std::move(params)) };
			}
			else
			{
				static_assert(methods::AuthorHas::getLast_name<T>, R"msg(Author::getLast_name is not implemented)msg");
				return { _pimpl->getLast_name() };
			}
		}

		service::AwaitableScalar<std::string> getEmail(service::FieldParams&& params) const final
		{
			if constexpr (methods::AuthorHas::getEmailWithParams<T>)
			{
				return { _pimpl->getEmail(std::move(params)) };
			}
			else
			{
				static_assert(methods::AuthorHas::getEmail<T>, R"msg(Author::getEmail is not implemented)msg");
				return { _pimpl->getEmail() };
			}
		}

		service::AwaitableScalar<std::string> getTitle(service::FieldParams&& params) const final
		{
			if constexpr (methods::AuthorHas::getTitleWithParams<T>)
			{
				return { _pimpl->getTitle(std::move(params)) };
			}
			else
			{
				static_assert(methods::AuthorHas::getTitle<T>, R"msg(Author::getTitle is not implemented)msg");
				return { _pimpl->getTitle() };
			}
		}

		void beginSelectionSet(const service::SelectionSetParams& params) const final
		{
			if constexpr (methods::AuthorHas::beginSelectionSet<T>)
			{
				_pimpl->beginSelectionSet(params);
			}
		}

		void endSelectionSet(const service::SelectionSetParams& params) const final
		{
			if constexpr (methods::AuthorHas::endSelectionSet<T>)
			{
				_pimpl->endSelectionSet(params);
			}
		}

	private:
		const std::shared_ptr<T> _pimpl;
	};

	Author(std::unique_ptr<const Concept>&& pimpl) noexcept;

	service::TypeNames getTypeNames() const noexcept;
	service::ResolverMap getResolvers() const noexcept;

	void beginSelectionSet(const service::SelectionSetParams& params) const final;
	void endSelectionSet(const service::SelectionSetParams& params) const final;

	const std::unique_ptr<const Concept> _pimpl;

public:
	template <class T>
	Author(std::shared_ptr<T> pimpl) noexcept
		: Author { std::unique_ptr<const Concept> { std::make_unique<Model<T>>(std::move(pimpl)) } }
	{
	}
};

} // namespace graphql::database::object

#endif // AUTHOROBJECT_H
