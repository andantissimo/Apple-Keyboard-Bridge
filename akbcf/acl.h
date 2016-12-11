/**
 * Apple Keyboard Bridge https://github.com/andantissimo/Apple-Keyboard-Bridge
 */
#pragma once

namespace Acl
{
	public ref class Principal
	{
	public:
		typedef System::Security::AccessControl::FileSystemRights Rights;

	public:
		static property Principal^ Current
		{
			Principal^ get()
			{
				return gcnew Principal(
					gcnew System::Security::Principal::WindowsPrincipal(
						System::Security::Principal::WindowsIdentity::GetCurrent()
						)
					);
			}
		}

	public:
		Principal(System::Security::Principal::WindowsPrincipal^ user)
			: _user(user)
		{
		}

		bool HasRight(System::Security::AccessControl::FileSystemSecurity^ sec, Rights right)
		{
			using namespace System::Security::Principal;
			using namespace System::Security::AccessControl;
			bool allowed = false;
			for each (FileSystemAccessRule^ rule in
			          sec->GetAccessRules(true, true, SecurityIdentifier::typeid))
			{
				SecurityIdentifier^ sid
					= static_cast<SecurityIdentifier^>(rule->IdentityReference);
				if ((rule->FileSystemRights == right ||
				     rule->FileSystemRights == FileSystemRights::FullControl) &&
				    _user->IsInRole(sid))
				{
					if (rule->AccessControlType == AccessControlType::Deny)
						return false;
					if (rule->AccessControlType == AccessControlType::Allow)
						allowed = true;
				}
			}
			return allowed;
		}
		bool HasRight(System::String^ path, Rights right)
		{
			using namespace System::IO;
			return File::Exists(path)
				? HasRight(File::GetAccessControl(path), right)
				: HasRight(Directory::GetAccessControl(Path::GetDirectoryName(path)), right);
		}

		void AddRight(System::Security::AccessControl::FileSystemSecurity^ sec, Rights right)
		{
			using namespace System::Security::Principal;
			using namespace System::Security::AccessControl;
			System::Collections::Generic::List<FileSystemAccessRule^> denies;
			bool allowed = false;
			for each (FileSystemAccessRule^ rule in
			          sec->GetAccessRules(true, true, SecurityIdentifier::typeid))
			{
				SecurityIdentifier^ sid
					= static_cast<SecurityIdentifier^>(rule->IdentityReference);
				if ((rule->FileSystemRights == right ||
					 rule->FileSystemRights == FileSystemRights::FullControl) &&
					_user->IsInRole(sid))
				{
					if (rule->AccessControlType == AccessControlType::Deny)
						denies.Add(rule);
					if (rule->AccessControlType == AccessControlType::Allow)
						allowed = true;
				}
			}
			for each (FileSystemAccessRule^ rule in denies) {
				sec->RemoveAccessRule(rule);
			}
			if (!allowed) {
				FileSystemAccessRule^ rule = gcnew FileSystemAccessRule(
					_user->Identity->Name, right, AccessControlType::Allow);
				sec->AddAccessRule(rule);
			}
		}
		void AddRight(System::String^ path, Rights right)
		{
			using namespace System::IO;
			using namespace System::Security::Principal;
			using namespace System::Security::AccessControl;
			if (File::Exists(path)) {
				FileSecurity^ sec = File::GetAccessControl(path);
				AddRight(sec, right);
				File::SetAccessControl(path, sec);
			} else {
				System::String^ dir = Path::GetDirectoryName(path);
				DirectorySecurity^ sec = Directory::GetAccessControl(dir);
				AddRight(sec, right);
				Directory::SetAccessControl(dir, sec);
			}
		}

	private:
		System::Security::Principal::WindowsPrincipal^ _user;
	};
}
