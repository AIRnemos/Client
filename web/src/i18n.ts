import { register, init, getLocaleFromNavigator } from 'svelte-i18n';

export default () => {
  register('en', () => import('./lang/en.json'));
  register('de', () => import('./lang/de.json'));

  init({
    fallbackLocale: 'en',
    initialLocale: getLocaleFromNavigator(),
  });
}
